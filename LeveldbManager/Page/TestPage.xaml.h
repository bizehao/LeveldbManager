#pragma once

#include "Layout/ImageGalleryPanel.h"
#include "TestPage.g.h"
#include "Layout/FlexLayout.h"
#include "ViewModel/MainPageViewModel.h"

namespace winrt::LeveldbManager::implementation
{

    struct ImageGalleryData : winrt::implements<ImageGalleryData, winrt::Windows::Foundation::IStringable>
    {
        ImageGalleryData(winrt::Windows::Foundation::Uri inImageUri, winrt::hstring inCounter, winrt::Microsoft::UI::Xaml::Visibility inOverlayVisiblity) :
            ImageUri{inImageUri}, Counter{inCounter}, OverlayVisiblity{inOverlayVisiblity} {}
        winrt::Windows::Foundation::Uri ImageUri;
        winrt::hstring Counter;
        winrt::Microsoft::UI::Xaml::Visibility OverlayVisiblity;

        winrt::hstring ToString() { return L"winrt::LeveldbManager::implementation::ImageGalleryData"; }
    };

    struct TestPage : TestPageT<TestPage>
    {
        TestPage();

        Windows::Foundation::IAsyncAction OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs e);

    private:
        Windows::Foundation::IAsyncAction SetItemsSource();

    public:
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    
    private:
        LeveldbManager::MainPageViewModel _view_model;
    };
} // namespace winrt::LeveldbManager::implementation

namespace winrt::LeveldbManager::factory_implementation
{
    struct TestPage : TestPageT<TestPage, implementation::TestPage>
    {
    };
} // namespace winrt::LeveldbManager::factory_implementation
