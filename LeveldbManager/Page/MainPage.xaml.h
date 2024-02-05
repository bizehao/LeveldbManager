#pragma once

#include "MainPage.g.h"
#include <leveldb/db.h>
#include "Data/ComLevelDB.h"
#include "Data/TabData.h"
#include "ViewModel/MainPageViewModel.h"

struct AABB
{
    int a;
    double b;
};

namespace winrt::LeveldbManager::implementation
{

    struct CCDD
    {
        int a;
        double b;
    };
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();
        ~MainPage();

        void InitializeComponent();

        winrt::Microsoft::UI::Windowing::AppWindow AppWindow();

        void ContentTabView_TabCloseRequested(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender,
                                              winrt::Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs const& args);
        Windows::Foundation::IAsyncAction CreateNewConnect(winrt::Windows::Foundation::IInspectable const& sender,
                                                           winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void closeTab(LeveldbManager::Contact contact, hstring key);
        void deleteKey(LeveldbManager::Contact contact, hstring key);

        LeveldbManager::MainPageViewModel ViewModel() { return _ViewModel; }

        leveldb::DB* getDB(int index);

        Windows::Foundation::IAsyncAction CreateNewDB_Click(winrt::Windows::Foundation::IInspectable const& sender,
                                                            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);;
    private:
        LeveldbManager::TabData CreateNewMyData(LeveldbManager::Contact contact, const hstring& title, const hstring& key,
                                                       const hstring& value);
        Windows::Foundation::IAsyncAction InsertNewDB(const hstring& path);

        std::vector<ComLevelDB> _leveldbs;

        leveldb::DB* _cur_leveldb{nullptr};

        winrt::apartment_context _ui_thread;

        LeveldbManager::MainPageViewModel _ViewModel;

        winrt::event_token _SelectedIndex_token;

    public:
        void ContentTabView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender,
                                             winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        Windows::Foundation::IAsyncAction
        ContentTabView_TabItemsChanged(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender,
                                       winrt::Windows::Foundation::Collections::IVectorChangedEventArgs const& args);

        void MenuFlyoutItem_Click_CloseSelf(winrt::Windows::Foundation::IInspectable const& sender,
                                            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void MenuFlyoutItem_Click_CloseOther(winrt::Windows::Foundation::IInspectable const& sender,
                                             winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void KeyList_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ContentTabView_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    
        void say() {
            
        }
    };
}

namespace winrt::LeveldbManager::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
