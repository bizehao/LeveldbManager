#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

#include <shobjidl_core.h>
#include <microsoft.ui.xaml.window.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Microsoft.UI.Composition.Interop.h>
#include <format>
#include "TabContentPage.xaml.h"
#include "App.xaml.h"
#include <leveldb/db.h>
#include "Util/Utils.h"
#include <array>
#include <thread>
#include "Data/ComLevelDB.h"
#include "Dialog/NewDbDialog.xaml.h"
#include <filesystem>
#include "Util/SimpleDialog.h"
#include "Util/CppWinRTHelpers.h"
#include <winrt/Windows.Storage.Pickers.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Storage::Pickers;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Windows::Storage::Pickers;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::LeveldbManager::implementation
{
    constexpr int MinWidth = 1000;
    constexpr int MinHeight = 600;

    LRESULT CALLBACK handle_event(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
    {
        switch (message)
        {
        case WM_GETMINMAXINFO:
            MINMAXINFO* p = (MINMAXINFO*)lparam;
            p->ptMinTrackSize.x = MinWidth;
            p->ptMinTrackSize.y = MinHeight;
            break;
        }
        return DefSubclassProc(hwnd, message, wparam, lparam);
    }

    MainPage::MainPage()
    {  
    }

    MainPage::~MainPage()
    {
        App::Window()->ViewModel().PropertyChanged(_SelectedIndex_token);
        for (auto& db : _leveldbs)
        {
            db->Close();
        }
    }

    void MainPage::InitializeComponent() {
        MainPageT::InitializeComponent();
        bool result = SetWindowSubclass(App::Window()->GetHWND(), handle_event, 101, 0);
        assert(result);
        Microsoft::UI::Windowing::AppWindow appWindow = AppWindow();
        appWindow.Resize({1200, 800});

        KeyList().SelectionMode(Microsoft::UI::Xaml::Controls::ListViewSelectionMode::None);
        
        //订阅事件
        winrt::event_token token = KeyList().SizeChanged([this](Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::SizeChangedEventArgs const& e) {
            _ViewModel.KeyListHeight(e.NewSize().Height);
        });
        //取消事件
        KeyList().SizeChanged(token);
        

        _SelectedIndex_token = App::Window()->ViewModel().PropertyChanged([this](Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e) {
            if (e.PropertyName() == L"SelectedIndex")
            {
                auto selectedIndex = App::Window()->ViewModel().SelectedIndex();
                ContentTabView().SelectedIndex(selectedIndex);
            }
        });
    }

    void MainPage::KeyList_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
    {
        KeyList().ItemsSource(App::Window()->ViewModel().Contacts()); 
    }

    winrt::Microsoft::UI::Windowing::AppWindow MainPage::AppWindow()
    {
        HWND hWnd = App::Window()->GetHWND();
        Microsoft::UI::WindowId windowId = winrt::Microsoft::UI::GetWindowIdFromWindow(hWnd);
        Microsoft::UI::Windowing::AppWindow appWindow = Microsoft::UI::Windowing::AppWindow::GetFromWindowId(windowId);
        return appWindow;
    }

    Windows::Foundation::IAsyncAction MainPage::InsertNewDB(const hstring& path)
    {
        auto folder = co_await Windows::Storage::StorageFolder::GetFolderFromPathAsync(path);
        auto files = co_await folder.GetFilesAsync();
        static const std::array<hstring, 3> comparison_files = {L"CURRENT", L"LOCK", L"LOG"};
        bool has_CURRENT = false;
        bool has_LOCK = false;
        bool has_LOG = false;
        for (auto item : files)
        {
            if (!has_CURRENT && item.Name() == comparison_files[0])
            {
                has_CURRENT = true;
            }
            if (!has_LOCK && item.Name() == comparison_files[1])
            {
                has_LOCK = true;
            }
            if (!has_LOG && item.Name() == comparison_files[2])
            {
                has_LOG = true;
            }
            if (has_CURRENT && has_LOCK && has_LOG)
            {
                break;
            }
        }

        if (has_CURRENT && has_LOCK && has_LOG)
        {
            auto path = folder.Path();
            leveldb::DB* db = nullptr;
            leveldb::Options options;
            options.create_if_missing = true;
            std::wstring wstr_name{static_cast<std::wstring_view>(path)};
            leveldb::Status status = leveldb::DB::Open(options, utils::wstring_to_string(wstr_name), &db);
            if (status.ok())
            {
                auto comDB = winrt::make_self<ComLevelDBImpl>(db);
                _leveldbs.push_back(comDB);
                auto pppxx = folder.Name();
                LeveldbManager::Contact contact{*comDB, KeyList(), folder.Name(), path};
                App::Window()->ViewModel().Contacts().Append(std::move(contact));
            }
            else
            {
                //数据库打开失败
                co_await dialog::showSimpleDialog(Content().XamlRoot(), L"数据库可能被占用,无法打开");
            }
        }
        else
        {
            //不是一个leveldb数据库
            co_await dialog::showSimpleDialog(Content().XamlRoot(), L"这不是一个leveldb数据库");
        }
    }

    leveldb::DB* MainPage::getDB(int index) { return _leveldbs[index]->DB(); }

    void MainPage::ContentTabView_TabCloseRequested(
        winrt::Microsoft::UI::Xaml::Controls::TabView const& sender,
        winrt::Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs const& args)
    {

        auto item = args.Item();
        uint32_t ii = -1;
        bool result = ContentTabView().TabItems().IndexOf(item, ii);
        if (result)
        {
            App::Window()->ViewModel().TabDatas().RemoveAt(ii);
        }
    }

    Windows::Foundation::IAsyncAction MainPage::CreateNewConnect(winrt::Windows::Foundation::IInspectable const& sender,
                                                                               winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        FolderPicker picker;
        picker.as<IInitializeWithWindow>()->Initialize(App::Window()->GetHWND());
        picker.SuggestedStartLocation(PickerLocationId::ComputerFolder);
        picker.FileTypeFilter().Append(L"*");
        if (auto folder = co_await picker.PickSingleFolderAsync())
        {
            InsertNewDB(folder.Path());
        }
    }

    void MainPage::closeTab(LeveldbManager::Contact contact, hstring key)
    {
        auto tabDatas = App::Window()->ViewModel().TabDatas();
        auto result = std::find_if(tabDatas.begin(), tabDatas.end(), [contact, key](auto p) { return p.Contact() == contact && p.Key() == key; });
        int index = std::distance(tabDatas.begin(), result);
        tabDatas.RemoveAt(index);
    }

    void MainPage::deleteKey(LeveldbManager::Contact contact, hstring key) {}

    void MainPage::ContentTabView_SelectionChanged(
        winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
    {
        int index = ContentTabView().SelectedIndex();
        if (index != -1)
        {
            auto tabDatas = App::Window()->ViewModel().TabDatas();
            auto it = tabDatas.GetAt(index);
            auto contact = it.Contact();
            contact.IsExpanded(true);
            contact.SelectedKey(it.Key());
        }
    }

    Windows::Foundation::IAsyncAction MainPage::ContentTabView_TabItemsChanged(
        winrt::Microsoft::UI::Xaml::Controls::TabView const& sender, winrt::Windows::Foundation::Collections::IVectorChangedEventArgs const& args)
    {
        static LeveldbManager::Contact oneRemainContact;
        if (ContentTabView().TabItems().Size() == 1)
        {
            auto tabDatas = App::Window()->ViewModel().TabDatas();
            auto it = tabDatas.GetAt(0);
            auto contact = it.Contact();
            oneRemainContact = contact;
        }

        int index = args.Index();
        auto changeType = args.CollectionChange();
        if (changeType == Windows::Foundation::Collections::CollectionChange::ItemInserted)
        {
            co_await resume_after(std::chrono::milliseconds(50));
            co_await _ui_thread;
            if (ContentTabView().ContainerFromIndex(index))
            {
                ContentTabView().SelectedIndex(index);
            }
        }
        else if (changeType == Windows::Foundation::Collections::CollectionChange::ItemRemoved)
        {
            if (ContentTabView().TabItems().Size() == 0)
            {
                oneRemainContact.IsExpanded(true);
                oneRemainContact.SelectedKey({});
            }
        }
    }

    Windows::Foundation::IAsyncAction MainPage::CreateNewDB_Click(winrt::Windows::Foundation::IInspectable const& sender,
                                                                                winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {

        LeveldbManager::NewDbDialog newDbDialog;
        ContentDialog filesDialog;
        filesDialog.XamlRoot(Content().XamlRoot());
        filesDialog.Title(box_value(L"请输入数据库名称"));
        filesDialog.Content(newDbDialog);
        filesDialog.PrimaryButtonText(L"确定");
        filesDialog.CloseButtonText(L"取消");
        auto result = co_await filesDialog.ShowAsync();
        if (result == ContentDialogResult::Primary)
        {
            auto tb = filesDialog.Content().as<LeveldbManager::NewDbDialog>();
            hstring dbName = tb.DbName().Text();
            hstring dbPath = tb.DbPath().Text();
            if (dbName.empty() || dbPath.empty())
            {
                co_await dialog::showSimpleDialog(Content().XamlRoot(), L"信息填写不完整");
            }
            else
            {
                auto tStrPath = winrt::to_string(dbPath);
                std::filesystem::path volidPath{tStrPath};
                if (!std::filesystem::exists(volidPath))
                {
                    co_await dialog::showSimpleDialog(Content().XamlRoot(), L"目录不存在");
                }
                else
                {
                    //创建数据库
                    leveldb::DB* db = nullptr;
                    leveldb::Options options;
                    options.create_if_missing = true;
                    auto tStrName = winrt::to_string(dbName);
                    volidPath /= tStrName;
                    auto tDbPath = volidPath.string();
                    leveldb::Status status = leveldb::DB::Open(options, tDbPath.c_str(), &db);
                    if (!status.ok())
                    {
                        co_await dialog::showSimpleDialog(Content().XamlRoot(), L"数据库创建失败");
                    }
                    else
                    {
                        co_await dialog::showSimpleDialog(Content().XamlRoot(), dbName + L" 创建成功");
                        auto tVolidPath = volidPath.string();
                        auto folderNmae = volidPath.filename().string();
                        auto comDB = winrt::make_self<ComLevelDBImpl>(db);
                        _leveldbs.push_back(comDB);
                        LeveldbManager::Contact contact{*comDB, KeyList(), winrt::to_hstring(folderNmae), winrt::to_hstring(tVolidPath)};
                        auto contacts = App::Window()->ViewModel().Contacts();
                        contacts.Append(std::move(contact));
                    }
                }
            }
        }
    }

    void MainPage::MenuFlyoutItem_Click_CloseSelf(winrt::Windows::Foundation::IInspectable const& sender,
                                                                                                  winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto tabDatas = App::Window()->ViewModel().TabDatas();
        auto menuFlyoutItem = sender.as<Controls::MenuFlyoutItem>();
        auto tag = menuFlyoutItem.Tag().as<winrt::hstring>();
        auto result = std::find_if(tabDatas.begin(), tabDatas.end(), [tag](LeveldbManager::TabData it) { return it.Id() == tag; });
        assert(result != tabDatas.end());
        int index = std::distance(tabDatas.begin(), result);
        tabDatas.RemoveAt(index);
    }

    void MainPage::MenuFlyoutItem_Click_CloseOther(winrt::Windows::Foundation::IInspectable const& sender,
                                                                                                   winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto menuFlyoutItem = sender.as<Controls::MenuFlyoutItem>();
        auto tag = menuFlyoutItem.Tag().as<winrt::hstring>();
        auto tabDatas = App::Window()->ViewModel().TabDatas();
        for (int i = 0; i < tabDatas.Size();)
        {
            if (tabDatas.GetAt(i).Id() == tag)
            {
                i++;
            }
            else
            {
                tabDatas.RemoveAt(i);
            }
        }
    }

    void MainPage::ContentTabView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        ContentTabView().TabItemsSource(App::Window()->ViewModel().TabDatas());
    }
} // namespace winrt::LeveldbManager::loadListViewData
