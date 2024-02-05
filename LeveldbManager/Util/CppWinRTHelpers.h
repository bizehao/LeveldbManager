#pragma once

#include <winrt/base.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include "GlobalDependencyProperty.h"
#include <winrt/Windows.Foundation.h>
#include <format>
#include <winrt/Windows.Management.Deployment.h>

namespace utils {

    // Helper to provide default values and boxing without differences at the call sites
    template <typename T, typename Enable = void>
    struct ValueHelper {
        static T GetDefaultValue() {
#pragma warning(push)
#pragma warning(disable : 26444)
            return T{};
#pragma warning(pop)
        }

        static winrt::Windows::Foundation::IInspectable BoxValueIfNecessary(T const& value) { return winrt::box_value(value); }

        static T CastOrUnbox(winrt::Windows::Foundation::IInspectable const& value) { return winrt::unbox_value<T>(value); }

        static winrt::Windows::Foundation::IInspectable BoxedDefaultValue() { return BoxValueIfNecessary(GetDefaultValue()); }
    };

    template <typename T>
    struct ValueHelper<T, std::enable_if_t<std::is_base_of_v<winrt::Windows::Foundation::IUnknown, T>>> {
        static T GetDefaultValue() { return T{nullptr}; }

        static winrt::Windows::Foundation::IInspectable BoxValueIfNecessary(T const& value) { return value; }

        static T CastOrUnbox(winrt::Windows::Foundation::IInspectable const& value) { return value.as<T>(); }

        static winrt::Windows::Foundation::IInspectable BoxedDefaultValue() { return GetDefaultValue(); }
    };

    template <>
    struct ValueHelper<winrt::hstring, void> {
        static winrt::hstring GetDefaultValue() { return winrt::hstring{L""}; }

        static winrt::Windows::Foundation::IInspectable BoxValueIfNecessary(winrt::hstring const& value) { return winrt::box_value(value); }

        static winrt::hstring CastOrUnbox(winrt::Windows::Foundation::IInspectable const& value) { return winrt::unbox_value<winrt::hstring>(value); }

        static winrt::Windows::Foundation::IInspectable BoxedDefaultValue() { return winrt::box_value(L""); }
    };

    inline winrt::Microsoft::UI::Xaml::DependencyProperty
    InitializeDependencyProperty(std::wstring_view const& propertyNameString, std::wstring_view const& propertyTypeNameString,
                                 std::wstring_view const& ownerTypeNameString, bool isAttached,
                                 winrt::Windows::Foundation::IInspectable const& defaultValue,
                                 winrt::Microsoft::UI::Xaml::PropertyChangedCallback const& propertyChangedCallback = nullptr) {
        auto propertyType = winrt::Windows::UI::Xaml::Interop::TypeName();
        propertyType.Name = propertyTypeNameString;
        propertyType.Kind = winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata;

        auto ownerType = winrt::Windows::UI::Xaml::Interop::TypeName{};
        ownerType.Name = ownerTypeNameString;
        ownerType.Kind = winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata;

        auto propertyMetadata = winrt::Microsoft::UI::Xaml::PropertyMetadata{defaultValue, propertyChangedCallback};

        if (isAttached) {
            return winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(propertyNameString, propertyType, ownerType, propertyMetadata);
        } else {
            return winrt::Microsoft::UI::Xaml::DependencyProperty::Register(propertyNameString, propertyType, ownerType, propertyMetadata);
        }
    }

    template <typename D, typename T>
    winrt::com_ptr<D> as_self(T&& o) {
        winrt::com_ptr<D> result;
        if constexpr (std::is_same_v<std::remove_cvref_t<T>, winrt::Windows::Foundation::IInspectable>) {
            auto temp = o.as<winrt::default_interface<D>>();
            result.attach(winrt::get_self<D>(temp));
            winrt::detach_abi(temp);
        } else if constexpr (std::is_rvalue_reference_v<T&&>) {
            result.attach(winrt::get_self<D>(o));
            winrt::detach_abi(o);
        } else {
            result.copy_from(winrt::get_self<D>(o));
        }

        return result;
    }

    bool registerSparsePackage(winrt::hstring externalLocation, winrt::hstring sparsePkgPath);

} // namespace utils