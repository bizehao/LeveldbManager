#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "ContentControl.g.h"

namespace winrt::LeveldbManager::implementation
{
    struct ContentControl : ContentControlT<ContentControl>
    {
        ContentControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::LeveldbManager::factory_implementation
{
    struct ContentControl : ContentControlT<ContentControl, implementation::ContentControl>
    {
    };
}
