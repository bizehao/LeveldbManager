#include "pch.h"
#include "ContentControl.xaml.h"
#if __has_include("ContentControl.g.cpp")
#include "ContentControl.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::LeveldbManager::implementation
{
    ContentControl::ContentControl()
    {
        InitializeComponent();
    }

    int32_t ContentControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ContentControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void ContentControl::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
