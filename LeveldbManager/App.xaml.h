#pragma once

#include "App.xaml.g.h"
#include "MainWindow.xaml.h"

namespace winrt::LeveldbManager::implementation
{
    struct App : AppT<App>
    {
        static impl::com_ref<MainWindow> Window();
        App();
        ~App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

        void OnNavigationFailed(IInspectable const&, Microsoft::UI::Xaml::Navigation::NavigationFailedEventArgs const& e);

    private:

        Microsoft::UI::Xaml::Controls::Frame CreateRootFrame();

        std::jthread _outThread;

        static Microsoft::UI::Xaml::Window window;
    };
}
