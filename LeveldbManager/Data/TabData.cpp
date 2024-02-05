#include "pch.h"
#include "TabData.h"
#include "TabData.g.cpp"
#include "Util/CppWinRTHelpers.h"

namespace winrt::LeveldbManager::implementation {

    TabData::TabData() : _data_icon_source{nullptr} {}

    hstring TabData::Id() { return winrt::to_hstring(Contact().Id()) + L"_" + Key(); }

    hstring TabData::DataHeader() { return _data_header; }
    void TabData::DataHeader(hstring const& value) { _data_header = value; }
    winrt::Microsoft::UI::Xaml::Controls::IconSource TabData::DataIconSource() { return _data_icon_source; }
    void TabData::DataIconSource(winrt::Microsoft::UI::Xaml::Controls::IconSource const& value) { _data_icon_source = value; }
    winrt::Windows::Foundation::IInspectable TabData::DataContent() { return _data_content; }
    void TabData::DataContent(winrt::Windows::Foundation::IInspectable const& value) { _data_content = value; }
    hstring TabData::Key() { return _key; }
    void TabData::Key(hstring const& key) { _key = key; }
    hstring TabData::Value() { return _value; }
    void TabData::Value(hstring const& value) { _value = value; }

    winrt::LeveldbManager::Contact TabData::Contact() { return _contact;
    }
    void TabData::Contact(winrt::LeveldbManager::Contact const& value) { _contact = value;
    }
} // namespace winrt::LeveldbManager::implementation
