// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include <winrt/base.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Interop.h>

namespace utils {

    // Helper to use instead of winrt::DependencyProperty in a static global. Avoids getting a dynamic initializer and
    // destructor, so it saves on dll size as well as avoids destructing a WinRT object at dll unload.
    struct GlobalDependencyProperty {
        GlobalDependencyProperty() = default;

        constexpr GlobalDependencyProperty(std::nullptr_t) {}

        // Can assign to nullptr which will free the DP.
        GlobalDependencyProperty& operator=(std::nullptr_t) {
            Property() = nullptr;
            return *this;
        }

        // Can also copy from winrt::DependencyProperty to transfer ownership for initialization.
        GlobalDependencyProperty& operator=(winrt::Microsoft::UI::Xaml::DependencyProperty const& other) {
            Property() = other;
            return *this;
        }

        GlobalDependencyProperty(winrt::Microsoft::UI::Xaml::DependencyProperty const& other) { Property() = other; }

        // Cannot copy or assign this helper because it is only for global static usage.
        GlobalDependencyProperty(GlobalDependencyProperty const&) = delete;
        GlobalDependencyProperty& operator=(GlobalDependencyProperty const& other) = delete;

        operator winrt::Microsoft::UI::Xaml::DependencyProperty() const { return Property(); }

        operator bool() const { return static_cast<bool>(m_dependencyProperty); }

        bool operator==(winrt::Microsoft::UI::Xaml::DependencyProperty const& other) const { return Property() == other; }

        bool operator==(nullptr_t) const { return Property() == nullptr; }

    private:
        winrt::Microsoft::UI::Xaml::DependencyProperty& Property() {
            return reinterpret_cast<winrt::Microsoft::UI::Xaml::DependencyProperty&>(m_dependencyProperty);
        }

        winrt::Microsoft::UI::Xaml::DependencyProperty const& Property() const {
            return reinterpret_cast<winrt::Microsoft::UI::Xaml::DependencyProperty const&>(m_dependencyProperty);
        }

        winrt::Windows::Foundation::IUnknown* m_dependencyProperty{nullptr};
    };

} // namespace utils
