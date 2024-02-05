#include "pch.h"
#include "FlexLayout.h"
#include "Flex.FlexBasis.g.cpp"
#if __has_include("FlexLayout.g.cpp")
#    include "FlexLayout.g.cpp"
#endif
#include "Util/CppWinRTHelpers.h"

using namespace winrt::LeveldbManager::Flex;
using namespace winrt;
using namespace Microsoft::UI::Xaml;

#define YGFunYGValueWrapper(fun)                     \
    static void fun(YGNodeRef item, YGValue ygValue) \
    {                                                \
        if (ygValue.unit == YGUnit::YGUnitPercent)   \
        {                                            \
            fun##Percent(item, ygValue.value);       \
        }                                            \
        else if (ygValue.unit == YGUnit::YGUnitAuto) \
        {                                            \
            fun##Auto(item);                         \
        }                                            \
        else                                         \
        {                                            \
            fun(item, ygValue.value);                \
        }                                            \
    }
#define YGFunYGValueWrapperNoAuto(fun)               \
    static void fun(YGNodeRef item, YGValue ygValue) \
    {                                                \
        if (ygValue.unit == YGUnit::YGUnitPercent)   \
        {                                            \
            fun##Percent(item, ygValue.value);       \
        }                                            \
        else                                         \
        {                                            \
            fun(item, ygValue.value);                \
        }                                            \
    }
// clang-format off
YGFunYGValueWrapper(YGNodeStyleSetWidth) 
YGFunYGValueWrapperNoAuto(YGNodeStyleSetMinWidth)
YGFunYGValueWrapperNoAuto(YGNodeStyleSetMaxWidth)
YGFunYGValueWrapper(YGNodeStyleSetHeight)
YGFunYGValueWrapperNoAuto(YGNodeStyleSetMinHeight)
YGFunYGValueWrapperNoAuto(YGNodeStyleSetMaxHeight)
    // clang-format on

    // To learn more about WinUI, the WinUI project structure,
    // and more about our project templates, see: http://aka.ms/winui-project-info.

    namespace winrt::LeveldbManager::Flex::implementation
{

    FlexBasis::FlexBasis(float length, bool isRelative) :
        _length{length}, _isRelative{isRelative} {}
    float FlexBasis::Length() { return _length; }
    bool FlexBasis::IsAuto() { return *this == Auto(); }
    bool FlexBasis::IsRelative() { return _isRelative; }
    winrt::LeveldbManager::Flex::FlexBasis FlexBasis::Auto()
    {
        static Flex::FlexBasis autoBasic{std::numeric_limits<float>::max(), false};
        return autoBasic;
    }
} // namespace winrt::LeveldbManager::Flex::implementation

namespace winrt::LeveldbManager::implementation
{

    FlexLayout::FlexLayout() { EnsureProperties(); }
    FlexLayout::~FlexLayout() { releaseYGResource(); }

    void FlexLayout::EnsureProperties()
    {
    }

    //依赖属性
    winrt::LeveldbManager::Flex::FlexDirection FlexLayout::Direction() { return GetValue(DirectionProperty()).as<FlexDirection>(); }
    void FlexLayout::Direction(winrt::LeveldbManager::Flex::FlexDirection const& value)
    {
        SetValue(DirectionProperty(), winrt::box_value(value));
    }

    winrt::LeveldbManager::Flex::FlexJustify FlexLayout::JustifyContent() { return GetValue(JustifyContentProperty()).as<FlexJustify>(); }
    void FlexLayout::JustifyContent(winrt::LeveldbManager::Flex::FlexJustify const& value)
    {
        SetValue(JustifyContentProperty(), winrt::box_value(value));
    }

    winrt::LeveldbManager::Flex::FlexAlignContent FlexLayout::AlignContent()
    {
        return GetValue(AlignContentProperty()).as<FlexAlignContent>();
    }
    void FlexLayout::AlignContent(winrt::LeveldbManager::Flex::FlexAlignContent const& value)
    {
        SetValue(AlignContentProperty(), winrt::box_value(value));
    }

    winrt::LeveldbManager::Flex::FlexAlignItems FlexLayout::AlignItems() { return GetValue(AlignItemsProperty()).as<FlexAlignItems>(); }
    void FlexLayout::AlignItems(winrt::LeveldbManager::Flex::FlexAlignItems const& value)
    {
        SetValue(AlignItemsProperty(), winrt::box_value(value));
    }

    winrt::LeveldbManager::Flex::FlexWrap FlexLayout::Wrap() { return GetValue(WrapProperty()).as<FlexWrap>(); }
    void FlexLayout::Wrap(winrt::LeveldbManager::Flex::FlexWrap const& value) { SetValue(WrapProperty(), winrt::box_value(value)); }

    //附加属性

    RenderUnit FlexLayout::GetHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<RenderUnit>(bindable.GetValue(HeightUnitProperty()));
    }
    void FlexLayout::SetHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, RenderUnit value)
    {
        bindable.SetValue(HeightUnitProperty(), winrt::box_value(value));
    }

    RenderUnit FlexLayout::GetWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<RenderUnit>(bindable.GetValue(WidthUnitProperty()));
    }
    void FlexLayout::SetWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, RenderUnit value)
    {
        bindable.SetValue(WidthUnitProperty(), winrt::box_value(value));
    }

    RenderUnit FlexLayout::GetMaxHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<RenderUnit>(bindable.GetValue(MaxHeightUnitProperty()));
    }
    void FlexLayout::SetMaxHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, RenderUnit value)
    {
        bindable.SetValue(MaxHeightUnitProperty(), winrt::box_value(value));
    }

    RenderUnit FlexLayout::GetMaxWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<RenderUnit>(bindable.GetValue(MaxWidthUnitProperty()));
    }
    void FlexLayout::SetMaxWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, RenderUnit value)
    {
        bindable.SetValue(MaxWidthUnitProperty(), winrt::box_value(value));
    }

    RenderUnit FlexLayout::GetMinHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<RenderUnit>(bindable.GetValue(MinHeightUnitProperty()));
    }
    void FlexLayout::SetMinHeightUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, RenderUnit value)
    {
        bindable.SetValue(MinHeightUnitProperty(), winrt::box_value(value));
    }

    RenderUnit FlexLayout::GetMinWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<RenderUnit>(bindable.GetValue(MinWidthUnitProperty()));
    }
    void FlexLayout::SetMinWidthUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, RenderUnit value)
    {
        bindable.SetValue(MinWidthUnitProperty(), winrt::box_value(value));
    }

    double FlexLayout::GetAspectRatio(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<double>(bindable.GetValue(AspectRatioProperty()));
    }
    void FlexLayout::SetAspectRatio(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, double value)
    {
        bindable.SetValue(AspectRatioProperty(), winrt::box_value(value));
    }

    int32_t FlexLayout::GetOrder(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<int32_t>(bindable.GetValue(OrderProperty()));
    }
    void FlexLayout::SetOrder(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, int32_t value)
    {
        bindable.SetValue(OrderProperty(), winrt::box_value(value));
    }

    double FlexLayout::GetGrow(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<double>(bindable.GetValue(GrowProperty()));
    }
    void FlexLayout::SetGrow(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, double value)
    {
        bindable.SetValue(GrowProperty(), winrt::box_value(value));
    }

    double FlexLayout::GetShrink(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<double>(bindable.GetValue(ShrinkProperty()));
    }
    void FlexLayout::SetShrink(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable, double value)
    {
        bindable.SetValue(ShrinkProperty(), winrt::box_value(value));
    }

    winrt::LeveldbManager::Flex::FlexAlignSelf FlexLayout::GetAlignSelf(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<FlexAlignSelf>(bindable.GetValue(AlignSelfProperty()));
    }
    void FlexLayout::SetAlignSelf(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                                  winrt::LeveldbManager::Flex::FlexAlignSelf const& value)
    {
        bindable.SetValue(AlignSelfProperty(), winrt::box_value(value));
    }

    winrt::LeveldbManager::Flex::FlexBasis FlexLayout::GetBasis(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<FlexBasis>(bindable.GetValue(BasisProperty()));
    }
    void FlexLayout::SetBasis(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                              winrt::LeveldbManager::Flex::FlexBasis const& value)
    {
        bindable.SetValue(BasisProperty(), winrt::box_value(value));
    }

    winrt::LeveldbManager::Flex::RenderUnit FlexLayout::GetBasisUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<RenderUnit>(bindable.GetValue(BasisUnitProperty()));
    }
    void FlexLayout::SetBasisUnit(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                                  winrt::LeveldbManager::Flex::RenderUnit const& value)
    {
        bindable.SetValue(BasisUnitProperty(), winrt::box_value(value));
    }

    winrt::LeveldbManager::Flex::FlexPosition FlexLayout::GetPosition(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable)
    {
        return winrt::unbox_value<FlexPosition>(bindable.GetValue(PositionProperty()));
    }
    void FlexLayout::SetPosition(winrt::Microsoft::UI::Xaml::DependencyObject const& bindable,
                                 winrt::LeveldbManager::Flex::FlexPosition const& value)
    {
        bindable.SetValue(PositionProperty(), winrt::box_value(value));
    }

    //属性改变回调
    void FlexLayout::OnFlexLayoutChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
                                         const winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs& args)
    {
        /*auto parentElement = Media::VisualTreeHelper::GetParent(sender).try_as<UIElement>();
        if (parentElement) {
            parentElement.UpdateLayout();
        }*/
        auto self = sender.as<FlexLayout>();
        if (self)
        {
            self->UpdateLayout();
        }
    }
    void FlexLayout::OnFlexItemChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
                                       const winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs& args)
    {
        /*UIElement element = sender.as<UIElement>();
        element.UpdateLayout();*/
        auto self = Media::VisualTreeHelper::GetParent(sender).as<FlexLayout>();
        if (self)
        {
            self->UpdateLayout();
        }
    }

    winrt::Windows::Foundation::Size FlexLayout::MeasureOverride(winrt::Windows::Foundation::Size availableSize)
    {
        releaseYGResource();
        _nodeRoot = GetRoot(availableSize);

        for (int i = 0; i < Children().Size(); i++)
        {
            auto child = Children().GetAt(i);
            YGNodeInsertChild(_nodeRoot, GetChild(child, availableSize), i);
        }

        YGNodeCalculateLayout(_nodeRoot, YGUndefined, YGUndefined, YGDirection::YGDirectionInherit);
        uint32_t count = YGNodeGetChildCount(_nodeRoot);
        for (uint32_t i = 0; i < count; i++)
        {
            YGNodeRef child = YGNodeGetChild(_nodeRoot, i);
            auto [element] = *(reinterpret_cast<std::tuple<UIElement>*>(YGNodeGetContext(child)));
            float w = YGNodeLayoutGetWidth(child);
            float h = YGNodeLayoutGetHeight(child);
            element.Measure(Windows::Foundation::Size{w, h});
        }
        float w = YGNodeLayoutGetWidth(_nodeRoot);
        float h = YGNodeLayoutGetHeight(_nodeRoot);
        return Windows::Foundation::Size{w, h};
    }
    winrt::Windows::Foundation::Size FlexLayout::ArrangeOverride(winrt::Windows::Foundation::Size finalSize)
    {
        if (Children().Size() == 0)
        {
            return finalSize;
        }
        uint32_t count = YGNodeGetChildCount(_nodeRoot);
        for (uint32_t i = 0; i < count; i++)
        {
            YGNodeRef child = YGNodeGetChild(_nodeRoot, i);
            UIElement element = *(reinterpret_cast<UIElement*>(YGNodeGetContext(child)));
            float x = YGNodeLayoutGetLeft(child);
            float y = YGNodeLayoutGetTop(child);
            float w = YGNodeLayoutGetWidth(child);
            float h = YGNodeLayoutGetHeight(child);
            element.Arrange(Windows::Foundation::Rect{x, y, w, h});
        }
        /*float w = YGNodeLayoutGetWidth(_nodeRoot);
        float h = YGNodeLayoutGetHeight(_nodeRoot);
        w = std::isnan(w) ? 0 : w;
        h = std::isnan(h) ? 0 : h;*/

        return finalSize;
        //Windows::Foundation::Size{w, h};
    }

    YGValue FlexLayout::GetYogaValue(double value, RenderUnit unit)
    {
        if (std::isnan(value) || std::isinf(value))
        {
            return YGValueAuto;
        }
        YGValue result = {};
        result.value = value;
        if (unit == RenderUnit::Percentage)
        {
            result.unit = YGUnitPercent;
        }
        else if (unit == RenderUnit::Auto)
        {
            result.unit = YGUnitAuto;
        }
        else
        {
            result.unit = YGUnitPoint;
        }
        return result;
    }

    static constexpr YGAlign flexAlignContentToYGAlign(FlexAlignContent value)
    {
        YGAlign align = YGAlign::YGAlignAuto;
        switch (value)
        {
        case winrt::LeveldbManager::Flex::FlexAlignContent::Stretch:
            align = YGAlign::YGAlignStretch;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignContent::Center:
            align = YGAlign::YGAlignCenter;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignContent::Start:
            align = YGAlign::YGAlignFlexStart;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignContent::End:
            align = YGAlign::YGAlignFlexEnd;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignContent::SpaceBetween:
            align = YGAlign::YGAlignSpaceBetween;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignContent::SpaceAround:
            align = YGAlign::YGAlignSpaceAround;
            break;
        }
        return align;
    }
    static constexpr YGAlign flexAlignItemsToYGAlign(FlexAlignItems value)
    {
        YGAlign align = YGAlign::YGAlignAuto;
        switch (value)
        {
        case winrt::LeveldbManager::Flex::FlexAlignItems::Stretch:
            align = YGAlign::YGAlignStretch;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignItems::Center:
            align = YGAlign::YGAlignCenter;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignItems::Start:
            align = YGAlign::YGAlignFlexStart;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignItems::End:
            align = YGAlign::YGAlignFlexEnd;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignItems::Baseline:
            align = YGAlign::YGAlignBaseline;
            break;
        }
        return align;
    }
    static constexpr YGAlign flexAlignSelfToYGAlign(FlexAlignSelf value)
    {
        YGAlign align = YGAlign::YGAlignAuto;
        switch (value)
        {
        case winrt::LeveldbManager::Flex::FlexAlignSelf::Auto:
            align = YGAlign::YGAlignAuto;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignSelf::Stretch:
            align = YGAlign::YGAlignStretch;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignSelf::Center:
            align = YGAlign::YGAlignCenter;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignSelf::Start:
            align = YGAlign::YGAlignFlexStart;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignSelf::End:
            align = YGAlign::YGAlignFlexEnd;
            break;
        case winrt::LeveldbManager::Flex::FlexAlignSelf::Baseline:
            align = YGAlign::YGAlignBaseline;
            break;
        }
        return align;
    }

    YGNodeRef FlexLayout::GetRoot(Windows::Foundation::Size renderSize)
    {
        _config = YGConfigNew();
        auto root = YGNodeNewWithConfig(_config);
        YGNodeStyleSetFlexDirection(root, static_cast<YGFlexDirection>(Direction()));
        YGNodeStyleSetAlignItems(root, flexAlignItemsToYGAlign(AlignItems()));
        YGNodeStyleSetJustifyContent(root, static_cast<YGJustify>(JustifyContent()));
        YGNodeStyleSetAlignContent(root, flexAlignContentToYGAlign(AlignContent()));
        YGNodeStyleSetFlexWrap(root, static_cast<YGWrap>(Wrap()));
        YGNodeStyleSetWidth(root, renderSize.Width);
        YGNodeStyleSetHeight(root, renderSize.Height);

        return root;
    }

    static Thickness GetMartgin(DependencyObject obj) { return winrt::unbox_value<Thickness>(obj.GetValue(FrameworkElement::MarginProperty())); }

    YGNodeRef FlexLayout::GetChild(UIElement c, Windows::Foundation::Size availableSize)
    {

        auto item = YGNodeNewWithConfig(_config);
        auto margin = GetMartgin(c);
        YGNodeStyleSetAlignSelf(item, flexAlignSelfToYGAlign(GetAlignSelf(c)));
        YGNodeStyleSetFlexShrink(item, GetShrink(c));
        YGNodeStyleSetFlexGrow(item, GetGrow(c));
        YGNodeStyleSetAspectRatio(item, GetAspectRatio(c));
        YGNodeStyleSetPositionType(item, static_cast<YGPositionType>(GetPosition(c)));

        YGNodeStyleSetMargin(item, YGEdge::YGEdgeLeft, margin.Left);
        YGNodeStyleSetMargin(item, YGEdge::YGEdgeTop, margin.Top);
        YGNodeStyleSetMargin(item, YGEdge::YGEdgeRight, margin.Right);
        YGNodeStyleSetMargin(item, YGEdge::YGEdgeBottom, margin.Bottom);

        double width = winrt::unbox_value<double>(c.GetValue(FrameworkElement::WidthProperty()));
        YGValue widthYGValue = GetYogaValue(width, GetWidthUnit(c));
        YGNodeStyleSetWidth(item, widthYGValue);

        double height = winrt::unbox_value<double>(c.GetValue(FrameworkElement::HeightProperty()));
        YGValue heightYGValue = GetYogaValue(height, GetHeightUnit(c));
        YGNodeStyleSetHeight(item, heightYGValue);

        double maxWidth = winrt::unbox_value<double>(c.GetValue(FrameworkElement::MaxWidthProperty()));
        YGValue maxWidthYGValue = GetYogaValue(maxWidth, GetMaxWidthUnit(c));
        YGNodeStyleSetMaxWidth(item, maxWidthYGValue);

        double maxHeight = winrt::unbox_value<double>(c.GetValue(FrameworkElement::MaxHeightProperty()));
        YGValue maxHeightYGValue = GetYogaValue(maxHeight, GetMaxHeightUnit(c));
        YGNodeStyleSetMaxHeight(item, maxHeightYGValue);

        double minWidth = winrt::unbox_value<double>(c.GetValue(FrameworkElement::MinWidthProperty()));
        YGValue minWidthYGValue = GetYogaValue(minWidth, GetMinWidthUnit(c));
        YGNodeStyleSetMinWidth(item, minWidthYGValue);

        double minHeight = winrt::unbox_value<double>(c.GetValue(FrameworkElement::MinHeightProperty()));
        YGValue minHeightYGValue = GetYogaValue(minHeight, GetMinHeightUnit(c));
        YGNodeStyleSetMinHeight(item, minHeightYGValue);

        auto contextData = std::make_unique<std::tuple<UIElement>>(c);
        YGNodeSetContext(item, contextData.get());
        _cacheElementContextData.emplace_back(std::move(contextData));
        return item;
    }

    void FlexLayout::releaseYGResource()
    {
        _cacheElementContextData.clear();
        if (nullptr != _nodeRoot)
        {
            YGConfigFree(_config);
            _config = nullptr;
        }
        if (nullptr != _config)
        {
            YGNodeFreeRecursive(_nodeRoot);
            _nodeRoot = nullptr;
        }
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::DirectionProperty()
    {
        static auto property = utils::InitializeDependencyProperty(
            L"Direction", winrt::name_of<Flex::FlexDirection>(), winrt::name_of<FlexLayout>(), false,
            winrt::box_value(Flex::FlexDirection::Column),
            winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexLayoutChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::JustifyContentProperty()
    {
        static auto property = utils::InitializeDependencyProperty(
            L"JustifyContent", winrt::name_of<Flex::FlexJustify>(), winrt::name_of<FlexLayout>(), false,
            winrt::box_value(Flex::FlexJustify::Start), winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexLayoutChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::AlignContentProperty()
    {
        static auto property = utils::InitializeDependencyProperty(
            L"AlignContent", winrt::name_of<Flex::FlexAlignContent>(), winrt::name_of<FlexLayout>(), false,
            winrt::box_value(Flex::FlexAlignContent::Stretch), winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexLayoutChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::AlignItemsProperty()
    {
        static auto property = utils::InitializeDependencyProperty(
            L"AlignItems", winrt::name_of<Flex::FlexAlignItems>(), winrt::name_of<FlexLayout>(), false,
            winrt::box_value(Flex::FlexAlignItems::Stretch), winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexLayoutChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::WrapProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"Wrap", winrt::name_of<Flex::FlexWrap>(), winrt::name_of<FlexLayout>(), false,
                                                                   winrt::box_value(Flex::FlexWrap::NoWrap),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexLayoutChanged));
        return property;
    }
    //附加属性
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::HeightUnitProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"HeighUnit", winrt::name_of<RenderUnit>(), winrt::name_of<FlexLayout>(), true,
                                                                   winrt::box_value(RenderUnit::Undefined),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::WidthUnitProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"WidthUnit", winrt::name_of<RenderUnit>(), winrt::name_of<FlexLayout>(), true,
                                                                   winrt::box_value(RenderUnit::Undefined),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::MaxHeightUnitProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"MaxHeighUnit", winrt::name_of<RenderUnit>(), winrt::name_of<FlexLayout>(),
                                                                   true, winrt::box_value(RenderUnit::Undefined),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::MaxWidthUnitProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"MaxWidthUnit", winrt::name_of<RenderUnit>(), winrt::name_of<FlexLayout>(),
                                                                   true, winrt::box_value(RenderUnit::Undefined),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::MinHeightUnitProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"MinHeighUnit", winrt::name_of<RenderUnit>(), winrt::name_of<FlexLayout>(),
                                                                   true, winrt::box_value(RenderUnit::Undefined),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::MinWidthUnitProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"MinWidthUnit", winrt::name_of<RenderUnit>(), winrt::name_of<FlexLayout>(),
                                                                   true, winrt::box_value(RenderUnit::Undefined),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::AspectRatioProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"AspectRatio", winrt::name_of<double>(), winrt::name_of<FlexLayout>(), true,
                                                                   winrt::box_value(std::numeric_limits<double>::quiet_NaN()),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::OrderProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"Order", winrt::name_of<int>(), winrt::name_of<FlexLayout>(), true,
                                                                   utils::ValueHelper<int>::BoxedDefaultValue(),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::GrowProperty()
    {
        static auto property =
            utils::InitializeDependencyProperty(L"Grow", winrt::name_of<double>(), winrt::name_of<FlexLayout>(), true, winrt::box_value(0.0),
                                                winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::ShrinkProperty()
    {
        static auto property =
            utils::InitializeDependencyProperty(L"Shrink", winrt::name_of<double>(), winrt::name_of<FlexLayout>(), true, winrt::box_value(0.0),
                                                winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::AlignSelfProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"AlignSelf", winrt::name_of<Flex::FlexAlignSelf>(),
                                                                   winrt::name_of<FlexLayout>(), true, winrt::box_value(Flex::FlexAlignSelf::Auto),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::BasisProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"Basis", winrt::name_of<Flex::FlexBasis>(), winrt::name_of<FlexLayout>(), true,
                                                                   winrt::box_value(Flex::FlexBasis::Auto()),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::BasisUnitProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"BasisUnit", winrt::name_of<Flex::RenderUnit>(), winrt::name_of<FlexLayout>(),
                                                                   true, winrt::box_value(RenderUnit::Point),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }
    winrt::Microsoft::UI::Xaml::DependencyProperty FlexLayout::PositionProperty()
    {
        static auto property = utils::InitializeDependencyProperty(L"Position", winrt::name_of<Flex::FlexPosition>(), winrt::name_of<FlexLayout>(),
                                                                   true, winrt::box_value(Flex::FlexPosition::Relative),
                                                                   winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&OnFlexItemChanged));
        return property;
    }

} // namespace winrt::LeveldbManager::implementation
