#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include <atlbase.h>
#include <atlstr.h>
#include <fcntl.h>
#include <io.h>
#include <thread>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

static int pipeHandles[2];
constexpr int kBufferSize = 4096;
void ReadFunc(std::stop_token st, int readhandle)
{
    char buf[kBufferSize];
    int readBtyes;
    do {
        readBtyes = _read(readhandle, buf, kBufferSize);
        buf[readBtyes] = 0;
        OutputDebugString(CA2W{buf});
    } while (readBtyes && !st.stop_requested());
}

namespace winrt::LeveldbManager::implementation
{

    winrt::Microsoft::UI::Xaml::Window App::window{nullptr};

    impl::com_ref<MainWindow> App::Window()
    {
        return window.as<MainWindow>();
    }

    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    App::App()
    {

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e) {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif

#pragma warning(disable : 6031)
        //´òÓ¡Êä³ö
        AllocConsole();                          // create console
        ShowWindow(GetConsoleWindow(), SW_HIDE); // we hide the window, But it will flashes once
        FILE* reopenOut = nullptr;
        FILE* repoenErr = nullptr;
        freopen_s(&reopenOut, "CONOUT$", "w+t", stdout); // if we don't want to use console,we can alse use files
        freopen_s(&repoenErr, "CONOUT$", "w+t", stderr); //  freopen_s(&repoenErr, "err.log", "w+t", stderr);
        if (reopenOut == nullptr || repoenErr == nullptr)
        {
            return;
        }

        ::_pipe(pipeHandles, kBufferSize, _O_TEXT);
        int orignalH = ::_dup(_fileno(stdout)); // we don't care about the orignal handle
        ::_dup2(pipeHandles[1], _fileno(stdout));
        ::_dup2(pipeHandles[1], _fileno(stderr));
        _outThread = std::jthread{&ReadFunc, pipeHandles[0]};
#pragma warning(pop)
    }

    App::~App()
    {
        _outThread.request_stop();
    }

    /// <summary>
    /// Invoked when the application is launched.
    /// </summary>
    /// <param name="e">Details about the launch request and process.</param>
    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        window = make<MainWindow>();
        Microsoft::UI::Xaml::Controls::Frame rootFrame = CreateRootFrame();
        if (!rootFrame.Content())
        {
            //LeveldbManager::MainPage
            rootFrame.Navigate(xaml_typename<LeveldbManager::MainPage>());
        }
        window.Activate();
    }

    Microsoft::UI::Xaml::Controls::Frame App::CreateRootFrame()
    {
        Microsoft::UI::Xaml::Controls::Frame rootFrame{nullptr};
        auto content = window.Content();
        if (content)
        {
            rootFrame = content.try_as<Microsoft::UI::Xaml::Controls::Frame>();
        }

        // Don't repeat app initialization when the Window already has content,
        // just ensure that the window is active
        if (!rootFrame)
        {
            // Create a Frame to act as the navigation context
            rootFrame = Microsoft::UI::Xaml::Controls::Frame{};

            rootFrame.NavigationFailed({this, &App::OnNavigationFailed});

            // Place the frame in the current Window
            window.Content(rootFrame);
        }

        return rootFrame;
    }

    void App::OnNavigationFailed(IInspectable const&, Navigation::NavigationFailedEventArgs const& e)
    {

        throw hresult_error(E_FAIL, hstring(L"Failed to load Page ") + e.SourcePageType().Name);
    }
} // namespace winrt::LeveldbManager::implementation
