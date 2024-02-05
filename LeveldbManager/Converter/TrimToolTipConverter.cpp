#include "pch.h"
#include "TrimToolTipConverter.h"
#include "TrimToolTipConverter.g.cpp"

namespace winrt::LeveldbManager::implementation
{
    winrt::Windows::Foundation::IInspectable TrimToolTipConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        if (value == nullptr) {
            return box_value(Microsoft::UI::Xaml::Visibility::Collapsed);
        }

        auto textBlock = value.as<Microsoft::UI::Xaml::Controls::TextBlock>();

        bool isTrim = textBlock.IsTextTrimmed();

        if (isTrim) {
            return box_value(Microsoft::UI::Xaml::Visibility::Visible);
        } else {
            return box_value(Microsoft::UI::Xaml::Visibility::Collapsed);
        }
    }
    winrt::Windows::Foundation::IInspectable TrimToolTipConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        throw hresult_not_implemented();
    }
}
