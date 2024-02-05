#pragma once

#include "MainWindow.g.h"
#include "ViewModel/MainWindowViewModel.h"

namespace winrt::LeveldbManager::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow() = default;

        HWND GetHWND();

        winrt::LeveldbManager::MainWindowViewModel ViewModel();

    private:
        winrt::LeveldbManager::MainWindowViewModel _ViewModel;
    };
} // namespace winrt::LeveldbManager::implementation

namespace winrt::LeveldbManager::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
} // namespace winrt::LeveldbManager::factory_implementation
