#pragma once
#include "Contact.g.h"
//#include "ContactWrapper.g.h"
#include "Util/comm_macro.hpp"
#include <leveldb/db.h>
#include "ComLevelDB.h"

namespace winrt::LeveldbManager::implementation
{
    struct Contact : ContactT<Contact>, wil::notify_property_changed_base<Contact>
    {
        Contact();

        Contact(winrt::Windows::Foundation::IInspectable db, Microsoft::UI::Xaml::Controls::ListView const& listViewParent, hstring const& name,
                hstring const& path);
        wil::single_threaded_property<int> Id;
        wil::single_threaded_property<hstring> Name;
        wil::single_threaded_property<hstring> Path;

        wil::single_threaded_property<Windows::Foundation::IInspectable> Db;
        wil::single_threaded_property<Microsoft::UI::Xaml::Controls::ListView> ListViewParent;

        winrt::hstring SelectedKey();
        void SelectedKey(winrt::hstring value);

        wil::untyped_event<winrt::hstring> SelectedKeyChanged;

        wil::single_threaded_notifying_property<Windows::Foundation::Collections::IObservableVector<winrt::hstring>> KeyDatas{ORIGIN_INIT(KeyDatas, winrt::single_threaded_observable_vector<winrt::hstring>())};
        wil::single_threaded_notifying_property<bool> IsExpanded{ORIGIN_INIT(IsExpanded, false)};

    private:
        void init();

        hstring _selectedKey;
        static int idGen;
    };
} // namespace winrt::LeveldbManager::implementation
namespace winrt::LeveldbManager::factory_implementation
{
    struct Contact : ContactT<Contact, implementation::Contact>
    {
    };
} // namespace winrt::LeveldbManager::factory_implementation
