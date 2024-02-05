#include "pch.h"
#include "Contact.h"
#include "Contact.g.cpp"
//#include "ContactWrapper.g.cpp"
#include <random>
#include "Util/CppWinRTHelpers.h"

namespace winrt::LeveldbManager::implementation
{

    int Contact::idGen{0};

    Contact::Contact()
    {
        init();
    }
    Contact::Contact(winrt::Windows::Foundation::IInspectable db, Microsoft::UI::Xaml::Controls::ListView const& listViewParent, hstring const& name,
                     hstring const& path) :
        Db{db}, Id{idGen++}, ListViewParent{listViewParent}, Name{name}, Path{path}
    {
        init();
    }

    winrt::hstring Contact::SelectedKey() { return _selectedKey; }
    void Contact::SelectedKey(winrt::hstring value)
    {
        if (_selectedKey != value)
        {
            _selectedKey = value;
            SelectedKeyChanged.invoke(*this, _selectedKey);
        }
    }

    void Contact::init() {}
} // namespace winrt::LeveldbManager::implementation
