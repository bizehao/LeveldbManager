#pragma once
#include "MainPageViewModel.g.h"
#include "Util/comm_macro.hpp"

namespace winrt::LeveldbManager::implementation
{
    struct MainPageViewModel : MainPageViewModelT<MainPageViewModel>, wil::notify_property_changed_base<MainPageViewModel>
    {
        MainPageViewModel();

        wil::single_threaded_notifying_property<double> KeyListHeight{ORIGIN_INIT(KeyListHeight, 0)};
        wil::single_threaded_notifying_property<hstring> TestName{ORIGIN_INIT(TestName, L"test string")};

    };
} // namespace winrt::LeveldbManager::implementation
namespace winrt::LeveldbManager::factory_implementation
{
    struct MainPageViewModel : MainPageViewModelT<MainPageViewModel, implementation::MainPageViewModel>
    {
    };
} // namespace winrt::LeveldbManager::factory_implementation
