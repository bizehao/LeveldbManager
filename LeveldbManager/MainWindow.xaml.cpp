#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#    include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::LeveldbManager::implementation
{
    HWND MainWindow::GetHWND()
    {
        auto windowNative{this->m_inner.as<::IWindowNative>()};
        HWND hWnd{nullptr};
        windowNative->get_WindowHandle(&hWnd);
        return hWnd;
    }

    winrt::LeveldbManager::MainWindowViewModel MainWindow::ViewModel()
    {
        return _ViewModel;
    }
} // namespace winrt::LeveldbManager::implementation
