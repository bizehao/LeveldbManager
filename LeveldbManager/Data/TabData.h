#pragma once
#include "TabData.g.h"  
#include "ComLevelDB.h"

namespace winrt::LeveldbManager::implementation
{
    struct TabData : TabDataT<TabData>
    {
        TabData();

        hstring Id();
        hstring DataHeader();
        void DataHeader(hstring const& value);
        winrt::Microsoft::UI::Xaml::Controls::IconSource DataIconSource();
        void DataIconSource(winrt::Microsoft::UI::Xaml::Controls::IconSource const& value);
        winrt::Windows::Foundation::IInspectable DataContent();
        void DataContent(winrt::Windows::Foundation::IInspectable const& value);
        hstring Key();
        void Key(hstring const& key);
        hstring Value();
        void Value(hstring const& value);
        winrt::LeveldbManager::Contact Contact();
        void Contact(winrt::LeveldbManager::Contact const& value);

    private:
        hstring _data_header;
        hstring _key;
        hstring _value;
        winrt::Microsoft::UI::Xaml::Controls::IconSource _data_icon_source;
        winrt::Windows::Foundation::IInspectable _data_content;
        LeveldbManager::Contact _contact;
    };
}
namespace winrt::LeveldbManager::factory_implementation
{
    struct TabData : TabDataT<TabData, implementation::TabData>
    {
    };
}
