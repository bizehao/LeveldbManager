#include "pch.h"

#include "ShowDBListItem.xaml.h"
#if __has_include("ShowDBListItem.g.cpp")
#    include "ShowDBListItem.g.cpp"
#endif
#include "App.xaml.h"
#include "Data/CommData.h"
#include "Data/Contact.h"
#include "Dialog/NewKeyValueDialog.xaml.h"
#include "MainWindow.xaml.h"
#include "Util/CppWinRTHelpers.h"
#include "Util/SimpleDialog.h"
#include "Util/Utils.h"
#include <numbers>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::LeveldbManager::implementation
{

    //底部高度
    constexpr int bheight = 160;

    class MySupportIncrementalLoadingHandle : public winrt::implements<MySupportIncrementalLoadingHandle, ISupportIncrementalLoadingHandle>
    {
    public:
        MySupportIncrementalLoadingHandle()
        {

        }
        Windows::Foundation::IAsyncOperation<Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable>> LoadMoreItemsAsync(uint32_t count) {
            std::cout << "count: " << count << std::endl;
            auto vec = winrt::single_threaded_vector<Windows::Foundation::IInspectable>();
            for (int i = 0; i < 20; i++)
            {
                vec.Append(winrt::box_value(winrt::to_hstring(i)));
            }
            vvxx += 20;
            co_return vec;
        }
        bool HasMoreItems()
        {
            return vvxx < 100;
        }
    private:
        int vvxx{0};
    };

    ShowDBListItem::ShowDBListItem()
    {
    }

    void ShowDBListItem::ExpItem_Collapsed(winrt::Microsoft::UI::Xaml::Controls::Expander const& sender,
                                           winrt::Microsoft::UI::Xaml::Controls::ExpanderCollapsedEventArgs const& args)
    {
        removeListViewSizeListener();
    }

    static std::optional<int> findContactIndex(int id)
    {
        auto contacts = App::Window()->ViewModel().Contacts();
        for (int i = 0; i < contacts.Size(); i++)
        {
            if (contacts.GetAt(i).Id() == id)
            {
                return i;
            }
        }
        return std::nullopt;
    }

    Windows::Foundation::IAsyncAction ShowDBListItem::ExpItem_Expanding(winrt::Microsoft::UI::Xaml::Controls::Expander const& sender,
                                           winrt::Microsoft::UI::Xaml::Controls::ExpanderExpandingEventArgs const& args)
    {
        KeyListView().Height(Contact().ListViewParent().ActualHeight() - bheight);
        removeListViewSizeListener();
        _listViewSizeEventToken = Contact().ListViewParent().SizeChanged(
            [this](Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::SizeChangedEventArgs const& e) {
                if (ExpItem().IsExpanded())
                {
                    KeyListView().Height(e.NewSize().Height - bheight);
                }
            });
        co_await winrt::resume_background();
        auto optIndex = findContactIndex(Contact().Id());
        co_await wil::resume_foreground(DispatcherQueue());
        if (optIndex) {
            Contact().ListViewParent().ScrollIntoView(Contact().ListViewParent().Items().GetAt(optIndex.value()),
                                                      Microsoft::UI::Xaml::Controls::ScrollIntoViewAlignment::Leading);
        } else {
            std::terminate();
        }
    }

    void ShowDBListItem::removeListViewSizeListener()
    {
        if (_listViewSizeEventToken)
        {
            Contact().ListViewParent().SizeChanged(_listViewSizeEventToken);
        }

        _listViewSizeEventToken = {};
    }
    Windows::Foundation::IAsyncAction ShowDBListItem::KeyListLoaded(winrt::Windows::Foundation::IInspectable const& sender,
                                                                    winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        _db = utils::as_self<ComLevelDBImpl>(Contact().Db())->DB();
        auto items = winrt::single_threaded_observable_vector<hstring>();
        co_await winrt::resume_background();
        leveldb::Iterator* it = _db->NewIterator(leveldb::ReadOptions());

        for (it->SeekToFirst(); it->Valid(); it->Next())
        {
            hstring str_key = winrt::to_hstring(it->key().ToString());
            items.Append(str_key);
        }
        assert(it->status().ok()); // Check for any errors found during the scan
        delete it;
        co_await wil::resume_foreground(DispatcherQueue());
        Contact().KeyDatas(items);
        KeyListView().ItemsSource(Contact().KeyDatas());
    }

    // void ShowDBListItem::KeyListSelectionChanged(winrt::Windows::Foundation::IInspectable const& sender,
    //                                         winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e) {
    //     auto item = KeyList().SelectedItem();
    //     auto key = item.as<hstring>();
    //     /*co_await resume_background();
    //     std::string value;
    //     std::wstring wkey = static_cast<std::wstring>(key);
    //     leveldb::Status status = _db->Get(leveldb::ReadOptions(), utils::wstring_to_string(wkey), &value);
    //     assert(status.ok());
    //     co_await ui_thread;*/
    //     auto mWindow = App::Window();
    //     mWindow->insertTab(Id(), key);
    // }

    Windows::Foundation::IAsyncAction ShowDBListItem::KeyListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender,
                                                                            winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& e)
    {
        auto item = e.ClickedItem();
        auto key = item.as<hstring>();

        co_await resume_background();
        auto tabDatas = App::Window()->ViewModel().TabDatas();
        auto result = std::find_if(tabDatas.begin(), tabDatas.end(), [key, this](auto p) { return p.Contact() == _contact && p.Key() == key; });
        if (result != tabDatas.end())
        {
            int index = std::distance(tabDatas.begin(), result);
            co_await wil::resume_foreground(DispatcherQueue());
            App::Window()->ViewModel().SelectedIndex(index);
        }
        else
        {
            std::string value;
            std::wstring wkey = static_cast<std::wstring>(key);
            auto db = utils::as_self<ComLevelDBImpl>(_contact.Db());
            leveldb::Status status = db->DB()->Get({}, utils::wstring_to_string(wkey), &value);
            assert(status.ok());
            auto title = key + L"|" + _contact.Name();
            co_await wil::resume_foreground(DispatcherQueue());
            auto tabData = CreateNewMyData(_contact, title, key, hstring{utils::string_to_wstring(value)});
            tabDatas.Append(tabData);
        }
    }

    LeveldbManager::Contact ShowDBListItem::Contact() { return _contact; }
    void ShowDBListItem::Contact(LeveldbManager::Contact value)
    {
        if (_contact != value)
        {
            _contact = value;

            Contact().SelectedKeyChanged([this](winrt::Windows::Foundation::IInspectable const& sender, winrt::hstring const& args) {
                if (args.empty())
                {
                    KeyListView().SelectedIndex(-1);
                }
                else
                {
                    uint32_t index = -1;
                    bool result = Contact().KeyDatas().IndexOf(args, index);
                    assert(result);
                    KeyListView().SelectedIndex(index);
                    auto item = KeyListView().Items().GetAt(index);
                    KeyListView().ScrollIntoView(item);
                }
            });

            RaisePropertyChanged(L"Contact");
        }
    }

    Windows::Foundation::IAsyncAction ShowDBListItem::NewKey_Click(winrt::Windows::Foundation::IInspectable const& sender,
                                                                   winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        LeveldbManager::NewKeyValueDialog newKeyValueDialog;
        ContentDialog dialog;
        dialog.XamlRoot(Content().XamlRoot());
        dialog.Title(box_value(L"请输入键和值"));
        dialog.Content(newKeyValueDialog);
        dialog.PrimaryButtonText(L"确定");
        dialog.CloseButtonText(L"取消");
        auto result = co_await dialog.ShowAsync();
        if (result == ContentDialogResult::Primary)
        {
            auto tb = dialog.Content().as<LeveldbManager::NewKeyValueDialog>();
            auto keyString = newKeyValueDialog.DbName().Text();
            auto valueString = newKeyValueDialog.DbValue().Text();
            auto stdKeyString = winrt::to_string(keyString);
            auto result = _db->Put({}, stdKeyString, winrt::to_string(valueString));
            if (result.ok())
            {
                Contact().KeyDatas().Append(keyString);
                auto searchText = AutoSuggestBox().Text();
                if (!searchText.empty())
                {
                    auto stdSearchText = winrt::to_string(searchText);
                    if (stdKeyString.find(stdSearchText) != std::string::npos)
                    {
                        auto itemsSource = KeyListView().ItemsSource().as<Windows::Foundation::Collections::IObservableVector<hstring>>();
                        itemsSource.Append(keyString);
                    }
                }
                //dialog::showSimpleDialog(Content().XamlRoot(), L"添加数据成功");
            }
            else
            {
                co_await dialog::showSimpleDialog(Content().XamlRoot(), L"添加数据失败");
            }
        }
    }

    void ShowDBListItem::AutoSuggestBox_TextChanged(
        winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender,
        winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args)
    {
        if (args.Reason() == AutoSuggestionBoxTextChangeReason::UserInput)
        {
            if (sender.Text().empty())
            {
                KeyListView().ItemsSource(Contact().KeyDatas());
            }
            else
            {
                auto searchText = winrt::to_string(sender.Text());
                auto suitableItems = winrt::single_threaded_observable_vector<hstring>();
                std::transform(searchText.begin(), searchText.end(), searchText.begin(), tolower);
                for (auto it : Contact().KeyDatas())
                {
                    auto tmpStr = winrt::to_string(it);
                    std::transform(tmpStr.begin(), tmpStr.end(), tmpStr.begin(), tolower);
                    if (tmpStr.find(searchText) != std::string::npos)
                    {
                        suitableItems.Append(it);
                    }
                }
                KeyListView().ItemsSource(suitableItems);
            }
        }
    }

    LeveldbManager::TabData ShowDBListItem::CreateNewMyData(LeveldbManager::Contact contact, const hstring& title, const hstring& key,
                                                            const hstring& value)
    {
        LeveldbManager::TabData item;
        item.DataHeader(title);
        item.Key(key);
        item.Value(value);
        Microsoft::UI::Xaml::Controls::SymbolIconSource source;
        source.Symbol(Microsoft::UI::Xaml::Controls::Symbol::Placeholder);
        item.DataIconSource(source);
        item.Contact(contact);

        Microsoft::UI::Xaml::Controls::Frame frame;
        auto dbItem = winrt::make_self<DBItem>(contact, key, value);
        frame.Navigate(xaml_typename<LeveldbManager::TabContentPage>(), *dbItem);
        item.DataContent(frame);
        //INotifyCollectionChanged;
        return item;
    }

} // namespace winrt::LeveldbManager::implementation
