#include "pch.h"
#include "TestPage.xaml.h"
#if __has_include("TestPage.g.cpp")
#    include "TestPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI;
using namespace Microsoft::UI::Xaml;
using namespace Windows;
using namespace Windows::Storage;
using namespace Windows::Foundation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::LeveldbManager::implementation
{
    TestPage::TestPage()
    {
        DataContext(_view_model);
    }

    Windows::Foundation::IAsyncAction TestPage::OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs e)
    {
        co_await SetItemsSource();
    }

    Windows::Foundation::IAsyncAction TestPage::SetItemsSource()
    {
        //StorageFolder photosFolder = co_await Storage::StorageFolder::GetFolderFromPathAsync(L"C:\\Users\\BiZeHao\\Pictures\\Camera Roll");
        //auto files = co_await photosFolder.GetFilesAsync();

        //const int visibleItemsCount = 6;
        //int hiddenItemsCount = files.Size() - visibleItemsCount;

        //auto photos = winrt::single_threaded_observable_vector<Foundation::IInspectable>();
        ////files.Size()
        //for (int i = 0; i < 20; i++)
        //{
        //    //files.GetAt(i).Path()
        //    Windows::Foundation::Uri uri{L"C:\\Users\\BiZeHao\\Pictures\\Camera Roll\\test.png"};
        //    hstring counter = to_hstring(i + 1);
        //    Xaml::Visibility overlayVisiblity = hiddenItemsCount > 0 && i == visibleItemsCount - 1 ? Xaml::Visibility::Visible : Xaml::Visibility::Collapsed;
        //    
        //    auto dbItem = winrt::make_self<ImageGalleryData>(uri, counter, overlayVisiblity);

        //    photos.Append(*dbItem);
        //}
        //ItemsControl().ItemsSource(photos);
        co_return;
    }

    void TestPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        auto value = _view_model.TestName() + L"123";
        _view_model.TestName(value);
    }
} // namespace winrt::LeveldbManager::implementation


