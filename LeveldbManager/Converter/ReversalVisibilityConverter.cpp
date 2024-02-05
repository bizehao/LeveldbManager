#include "pch.h"
#include "ReversalVisibilityConverter.h"
#include "ReversalVisibilityConverter.g.cpp"

namespace winrt::LeveldbManager::implementation
{
    winrt::Windows::Foundation::IInspectable ReversalVisibilityConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        auto nv = value.as<bool>();
        if (nv) {
            return box_value(Microsoft::UI::Xaml::Visibility::Visible);
        } else {
            return box_value(Microsoft::UI::Xaml::Visibility::Collapsed);
        }
    }
    winrt::Windows::Foundation::IInspectable ReversalVisibilityConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language)
    {
        throw hresult_not_implemented();
    }
}
