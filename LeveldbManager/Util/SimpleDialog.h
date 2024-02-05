#pragma once

#include <winrt/Microsoft.UI.Xaml.Controls.h>

namespace dialog{
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> showSimpleDialog(winrt::Microsoft::UI::Xaml::XamlRoot const& value, const winrt::hstring& message);
}


