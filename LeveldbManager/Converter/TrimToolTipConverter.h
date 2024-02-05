#pragma once
#include "TrimToolTipConverter.g.h"


namespace winrt::LeveldbManager::implementation
{
    struct TrimToolTipConverter : TrimToolTipConverterT<TrimToolTipConverter>
    {
        TrimToolTipConverter() = default;

        winrt::Windows::Foundation::IInspectable Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
        winrt::Windows::Foundation::IInspectable ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, hstring const& language);
    };
}
namespace winrt::LeveldbManager::factory_implementation
{
    struct TrimToolTipConverter : TrimToolTipConverterT<TrimToolTipConverter, implementation::TrimToolTipConverter>
    {
    };
}
