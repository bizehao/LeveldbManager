#pragma once
#include "MainWindowViewModel.g.h"
#include "Util/comm_macro.hpp"

namespace winrt::LeveldbManager::implementation
{
    struct MainWindowViewModel : MainWindowViewModelT<MainWindowViewModel>, wil::notify_property_changed_base<MainWindowViewModel>
    {
        MainWindowViewModel();

        wil::single_threaded_property<Windows::Foundation::Collections::IObservableVector<winrt::LeveldbManager::TabData>> TabDatas{winrt::single_threaded_observable_vector<LeveldbManager::TabData>()};
        wil::single_threaded_property<Windows::Foundation::Collections::IObservableVector<winrt::LeveldbManager::Contact>> Contacts{winrt::single_threaded_observable_vector<LeveldbManager::Contact>()};
        wil::single_threaded_notifying_property<int32_t> SelectedIndex{ORIGIN_INIT(SelectedIndex, -1)};
    };
}
namespace winrt::LeveldbManager::factory_implementation
{
    struct MainWindowViewModel : MainWindowViewModelT<MainWindowViewModel, implementation::MainWindowViewModel>
    {
    };
}
