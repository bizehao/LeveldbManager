#pragma once

#include "winrt/Microsoft.UI.Xaml.h"
#include "winrt/Microsoft.UI.Xaml.Markup.h"
#include "winrt/Microsoft.UI.Xaml.Controls.Primitives.h"
#include "Flex.FlexBasis.g.h"
#include "FlexLayout.g.h"
#include <yoga/Yoga.h>

namespace winrt::LeveldbManager::Flex::implementation {
    struct FlexBasis : FlexBasisT<FlexBasis> {
        FlexBasis() = default;

        FlexBasis(float length, bool isRelative);
        float Length();
        bool IsAuto();
        bool IsRelative();
        static winrt::LeveldbManager::Flex::FlexBasis Auto();

    private:
        float _length{0};
        bool _isRelative{false};
    };
} // namespace winrt::LeveldbManager::Flex::implementation

namespace winrt::LeveldbManager::implementation {

    struct FlexLayout : FlexLayoutT<FlexLayout> {
        FlexLayout();
        ~FlexLayout();

        //依赖属性
        winrt::LeveldbManager::Flex::FlexDirection Direction();
        void Direction(winrt::LeveldbManager::Flex::FlexDirection const& value);
        winrt::LeveldbManager::Flex::FlexJustify JustifyContent();
        void JustifyContent(winrt::LeveldbManager::Flex::FlexJustify const& value);
        winrt::LeveldbManager::Flex::FlexAlignContent AlignContent();
        void AlignContent(winrt::LeveldbManager::Flex::FlexAlignContent const& value);
        winrt::LeveldbManager::Flex::FlexAlignItems AlignItems();
        void AlignItems(winrt::LeveldbManager::Flex::FlexAlignItems const& value);
        winrt::LeveldbManager::Flex::FlexWrap Wrap();
        void Wrap(winrt::LeveldbManager::Flex::FlexWrap const& value);

        //附加属性
        static winrt::LeveldbManager::Flex::RenderUnit GetHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                                      winrt::LeveldbManager::Flex::RenderUnit value);
        static winrt::LeveldbManager::Flex::RenderUnit GetWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                                     winrt::LeveldbManager::Flex::RenderUnit value);

        static winrt::LeveldbManager::Flex::RenderUnit GetMaxHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetMaxHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, winrt::LeveldbManager::Flex::RenderUnit value);
        
        static winrt::LeveldbManager::Flex::RenderUnit GetMaxWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetMaxWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, winrt::LeveldbManager::Flex::RenderUnit value);

        static winrt::LeveldbManager::Flex::RenderUnit GetMinHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetMinHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, winrt::LeveldbManager::Flex::RenderUnit value);
        static winrt::LeveldbManager::Flex::RenderUnit GetMinWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetMinWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, winrt::LeveldbManager::Flex::RenderUnit value);

        static double GetAspectRatio(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetAspectRatio(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, double value);
        
        static int32_t GetOrder(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetOrder(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, int32_t value);
        
        static double GetGrow(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetGrow(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, double value);
        
        static double GetShrink(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetShrink(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, double value);
        
        static winrt::LeveldbManager::Flex::FlexAlignSelf GetAlignSelf(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetAlignSelf(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                                 winrt::LeveldbManager::Flex::FlexAlignSelf const& value);
        static winrt::LeveldbManager::Flex::FlexBasis GetBasis(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetBasis(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                             winrt::LeveldbManager::Flex::FlexBasis const& value);
        static winrt::LeveldbManager::Flex::RenderUnit GetBasisUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetBasisUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                                 winrt::LeveldbManager::Flex::RenderUnit const& value);

        static winrt::LeveldbManager::Flex::FlexPosition GetPosition(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable);
        static void SetPosition(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                                winrt::LeveldbManager::Flex::FlexPosition const& value);

        //依赖属性
        static winrt::Microsoft::UI::Xaml::DependencyProperty DirectionProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty JustifyContentProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty AlignContentProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty AlignItemsProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty WrapProperty();
        
        //附加属性
        static winrt::Microsoft::UI::Xaml::DependencyProperty HeightUnitProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty WidthUnitProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty MaxHeightUnitProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty MaxWidthUnitProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty MinHeightUnitProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty MinWidthUnitProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty AspectRatioProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty OrderProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty GrowProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty ShrinkProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty AlignSelfProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty BasisProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty BasisUnitProperty();
        static winrt::Microsoft::UI::Xaml::DependencyProperty PositionProperty();

        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);

    private:
        void EnsureProperties();

        YGValue GetYogaValue(double value,
                             winrt::LeveldbManager::Flex::RenderUnit unit = winrt::LeveldbManager::Flex::RenderUnit::Point);

        YGNodeRef GetRoot(Windows::Foundation::Size renderSize);

        YGNodeRef GetChild(Microsoft::UI::Xaml::UIElement c, Windows::Foundation::Size availableSize);

        void releaseYGResource();

        static void OnFlexLayoutChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
                                        const winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs& args);
        static void OnFlexItemChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
                                      const winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs& args);

        YGNodeRef _nodeRoot{nullptr};
        YGConfigRef _config{nullptr};
        std::vector<std::unique_ptr<std::tuple<Microsoft::UI::Xaml::UIElement>>> _cacheElementContextData;
    };
} // namespace winrt::LeveldbManager::implementation

namespace winrt::LeveldbManager::Flex::factory_implementation {
    struct FlexBasis : FlexBasisT<FlexBasis, implementation::FlexBasis> {};
} // namespace winrt::LeveldbManager::Flex::factory_implementation

namespace winrt::LeveldbManager::factory_implementation {

    struct FlexLayout : FlexLayoutT<FlexLayout, implementation::FlexLayout> {};
} // namespace winrt::LeveldbManager::factory_implementation
