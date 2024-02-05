#pragma once
#include "ReversalVisibilityConverter.g.h"

namespace winrt::LeveldbManager::implementation
{
    struct ReversalVisibilityConverter : ReversalVisibilityConverterT<ReversalVisibilityConverter>
    {
        ReversalVisibilityConverter() = default;

        winrt::Windows::Foundation::IInspectable Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
        winrt::Windows::Foundation::IInspectable ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
    };
}
namespace winrt::LeveldbManager::factory_implementation
{
    struct ReversalVisibilityConverter : ReversalVisibilityConverterT<ReversalVisibilityConverter, implementation::ReversalVisibilityConverter>
    {
    };
}
