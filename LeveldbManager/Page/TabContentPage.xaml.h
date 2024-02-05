#pragma once

#include "TabContentPage.g.h"
#include "Util/comm_macro.hpp"
#include <leveldb/db.h>
#include "Data/CommData.h"

namespace winrt::LeveldbManager::implementation
{
    struct TabContentPage : TabContentPageT<TabContentPage>, wil::notify_property_changed_base<TabContentPage>
    {
        TabContentPage();

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

        void OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs e);

        void ShowKey_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ShowValue_LostFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Save_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void Flush_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        wil::single_threaded_notifying_property<hstring> Key{ORIGIN_INIT(Key)};
        wil::single_threaded_notifying_property<hstring> Value{ORIGIN_INIT(Value)};
    private:
        leveldb::DB* _db{nullptr};
        winrt::com_ptr<DBItem> _dbItem;
        hstring _realValue;

    public:
        void ValueDisplayType_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender,
                                               winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void DeleteKey_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::LeveldbManager::factory_implementation
{
    struct TabContentPage : TabContentPageT<TabContentPage, implementation::TabContentPage>
    {
    };
}
