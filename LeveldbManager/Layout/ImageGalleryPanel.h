#pragma once
#include "Util/GlobalDependencyProperty.h"
#include "ImageGalleryPanel.g.h"
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>

namespace winrt::LeveldbManager::implementation
{
    struct ImageGalleryPanel : ImageGalleryPanelT<ImageGalleryPanel>
    {
        ImageGalleryPanel();

        static winrt::Microsoft::UI::Xaml::DependencyProperty ItemsInFirstRowProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty ItemsInSecondRowProperty();
        int32_t ItemsInSecondRow();
        void ItemsInSecondRow(int32_t value);
        int32_t ItemsInFirstRow();
        void ItemsInFirstRow(int32_t value);

        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);

    private:

        static void OnPropertyChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
                                      const winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs& args);

        bool IsEmpty() { return Children() == nullptr || Children().Size() == 0; }
        int GetCount() {
            return std::min(ItemsInFirstRow() + ItemsInSecondRow(), static_cast<int32_t>(Children().Size()));
        }

        static utils::GlobalDependencyProperty _itemsInFirstRowProperty;
        static utils::GlobalDependencyProperty _itemsInSecondRowProperty;
    };
} // namespace winrt::LeveldbManager::implementation
namespace winrt::LeveldbManager::factory_implementation
{
    struct ImageGalleryPanel : ImageGalleryPanelT<ImageGalleryPanel, implementation::ImageGalleryPanel>
    {
    };
} // namespace winrt::LeveldbManager::factory_implementation
