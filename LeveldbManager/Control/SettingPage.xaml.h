#pragma once

#include "SettingPage.g.h"

namespace winrt::LeveldbManager::implementation
{
    struct SettingPage : SettingPageT<SettingPage>
    {
        SettingPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::LeveldbManager::factory_implementation
{
    struct SettingPage : SettingPageT<SettingPage, implementation::SettingPage>
    {
    };
}
