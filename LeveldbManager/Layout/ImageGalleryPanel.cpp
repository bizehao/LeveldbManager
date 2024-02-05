#include "pch.h"
#include "ImageGalleryPanel.h"
#include "Util/CppWinRTHelpers.h"
#include "ImageGalleryPanel.g.cpp"


using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::LeveldbManager::implementation
{

    utils::GlobalDependencyProperty ImageGalleryPanel::_itemsInFirstRowProperty;
    utils::GlobalDependencyProperty ImageGalleryPanel::_itemsInSecondRowProperty;

    ImageGalleryPanel::ImageGalleryPanel()
    {
        if (!_itemsInFirstRowProperty)
        {
            _itemsInFirstRowProperty = utils::InitializeDependencyProperty(
                L"ItemsInFirstRow", winrt::name_of<int32_t>(), winrt::name_of<ImageGalleryPanel>(), false,
                utils::ValueHelper<int32_t>::BoxedDefaultValue(), winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnPropertyChanged));
        }

        if (!_itemsInSecondRowProperty)
        {
            _itemsInSecondRowProperty = utils::InitializeDependencyProperty(
                L"ItemsInSecondRow", winrt::name_of<int32_t>(), winrt::name_of<ImageGalleryPanel>(), false,
                utils::ValueHelper<int32_t>::BoxedDefaultValue(), winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnPropertyChanged));
        }
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty ImageGalleryPanel::ItemsInFirstRowProperty()
    {
        return _itemsInFirstRowProperty;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty ImageGalleryPanel::ItemsInSecondRowProperty()
    {
        return _itemsInSecondRowProperty;
    }
    int32_t ImageGalleryPanel::ItemsInSecondRow()
    {
        return GetValue(ItemsInSecondRowProperty()).as<int32_t>();
    }
    void ImageGalleryPanel::ItemsInSecondRow(int32_t value)
    {
        SetValue(ItemsInSecondRowProperty(), winrt::box_value(value));
    }
    int32_t ImageGalleryPanel::ItemsInFirstRow()
    {
        return GetValue(ItemsInFirstRowProperty()).as<int32_t>();
    }
    void ImageGalleryPanel::ItemsInFirstRow(int32_t value)
    {
        SetValue(ItemsInFirstRowProperty(), winrt::box_value(value));
    }
    winrt::Windows::Foundation::Size ImageGalleryPanel::MeasureOverride(winrt::Windows::Foundation::Size availableSize)
    {
        if (IsEmpty() || ItemsInFirstRow() == 0 || ItemsInSecondRow() == 0)
            return Windows::Foundation::Size{0, 0};

        double firstRowItemWidth = availableSize.Width / ItemsInFirstRow();
        double secondRowItemWidth = availableSize.Width / ItemsInSecondRow();

        int count = GetCount();
        for (auto i = 0; i < count; i++)
        {
            auto childAvailableSize = i + 1 <= ItemsInFirstRow() ? Windows::Foundation::Size{static_cast<float>(firstRowItemWidth), availableSize.Height} : Windows::Foundation::Size{static_cast<float>(secondRowItemWidth), availableSize.Height};
            Children().GetAt(i).Measure(childAvailableSize);
        }

        double childrenDesiredHeight = Children().Size() <= ItemsInFirstRow() ? Children().GetAt(0).DesiredSize().Height : Children().GetAt(0).DesiredSize().Height + Children().GetAt(count - 1).DesiredSize().Height;

        double height = std::min(static_cast<double>(availableSize.Height), childrenDesiredHeight);

        return Windows::Foundation::Size{availableSize.Width, static_cast<float>(height)};
    }
    winrt::Windows::Foundation::Size ImageGalleryPanel::ArrangeOverride(winrt::Windows::Foundation::Size finalSize)
    {
        if (IsEmpty())
            return Windows::Foundation::Size{0, 0};

        double x = .0;
        double y = .0;

        int count = GetCount();
        for (int i = 0; i < count; i++)
        {
            Children().GetAt(i).Arrange(Windows::Foundation::Rect{Windows::Foundation::Point{static_cast<float>(x), static_cast<float>(y)}, Children().GetAt(i).DesiredSize()});

            x += Children().GetAt(i).DesiredSize().Width;
            if (i + 1 == ItemsInFirstRow())
            {
                x = .0;
                y = Children().GetAt(0).DesiredSize().Height;
            }
        }

        return finalSize;
    }
    void ImageGalleryPanel::OnPropertyChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
                                              const winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs& args)
    {   
        auto dependencyProperty = args.Property();
        if (dependencyProperty == _itemsInFirstRowProperty)
        {
            auto self = sender.as<ImageGalleryPanel>();
            self->InvalidateMeasure();
            self->InvalidateArrange();
        }
    }
} // namespace winrt::LeveldbManager::implementation
