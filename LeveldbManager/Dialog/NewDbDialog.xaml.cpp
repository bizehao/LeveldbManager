#include "pch.h"
#include "NewDbDialog.xaml.h"
#if __has_include("NewDbDialog.g.cpp")
#include "NewDbDialog.g.cpp"
#endif
#include "App.xaml.h"
#include "MainWindow.xaml.h"

//#include <windows.storage.pickers.h>
#include <winrt/Windows.Storage.Pickers.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

using namespace winrt::Windows::Storage::Pickers;
using namespace winrt::Windows::Foundation;

namespace winrt::LeveldbManager::implementation
{
    NewDbDialog::NewDbDialog()
    {
        InitializeComponent();
    }

} // namespace winrt::LeveldbManager::implementation

IAsyncAction
winrt::LeveldbManager::implementation::NewDbDialog::Button_Click(winrt::Windows::Foundation::IInspectable const& sender,
                                                                             winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
       FolderPicker picker;
       picker.as<IInitializeWithWindow>()->Initialize(App::Window()->GetHWND());
       picker.SuggestedStartLocation(PickerLocationId::ComputerFolder);
       picker.FileTypeFilter().Append(L"*");
       if (auto folder = co_await picker.PickSingleFolderAsync()) {
           DbPath().Text(folder.Path());
       }
}
