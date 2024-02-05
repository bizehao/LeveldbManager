#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "ShowDBListItem.g.h"
#include "Converter/TrimToolTipConverter.h"
#include "Converter/ReversalVisibilityConverter.h"
#include "Util/comm_macro.hpp"
#include <leveldb/db.h>

namespace winrt::LeveldbManager::implementation {
    struct ShowDBListItem : ShowDBListItemT<ShowDBListItem>, wil::notify_property_changed_base<ShowDBListItem>
    {
        ShowDBListItem();

        static winrt::Microsoft::UI::Xaml::DependencyProperty TestTextProperty();

        void ExpItem_Collapsed(winrt::Microsoft::UI::Xaml::Controls::Expander const& sender,
                               winrt::Microsoft::UI::Xaml::Controls::ExpanderCollapsedEventArgs const& args);
        Windows::Foundation::IAsyncAction ExpItem_Expanding(winrt::Microsoft::UI::Xaml::Controls::Expander const& sender,
                               winrt::Microsoft::UI::Xaml::Controls::ExpanderExpandingEventArgs const& args);

        Windows::Foundation::IAsyncAction KeyListLoaded(winrt::Windows::Foundation::IInspectable const& sender,
                                                        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /*void KeyListSelectionChanged(winrt::Windows::Foundation::IInspectable const& sender,
                                                                  winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);*/

        Windows::Foundation::IAsyncAction KeyListView_ItemClick(winrt::Windows::Foundation::IInspectable const& sender,
                                   winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& e);

        LeveldbManager::Contact Contact();
        void Contact(LeveldbManager::Contact value);

        Windows::Foundation::IAsyncAction NewKey_Click(winrt::Windows::Foundation::IInspectable const& sender,
                                                       winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void AutoSuggestBox_TextChanged(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& sender,
                                        winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs const& args);

    private:
        void removeListViewSizeListener();
        LeveldbManager::TabData CreateNewMyData(LeveldbManager::Contact contact, const hstring& title, const hstring& key,
                                                const hstring& value);

        leveldb::DB* _db;
        double _key_list_height{0.0};
        static winrt::Microsoft::UI::Xaml::DependencyProperty _test_text_property;
        winrt::event_token _listViewSizeEventToken;
        LeveldbManager::Contact _contact;
    };
} // namespace winrt::LeveldbManager::implementation

namespace winrt::LeveldbManager::factory_implementation {
    struct ShowDBListItem : ShowDBListItemT<ShowDBListItem, implementation::ShowDBListItem> {};
} // namespace winrt::LeveldbManager::factory_implementation
