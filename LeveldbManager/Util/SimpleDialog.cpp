#include "pch.h"
#include "SimpleDialog.h"

using namespace winrt::Microsoft::UI::Xaml;

winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult> dialog::showSimpleDialog(winrt::Microsoft::UI::Xaml::XamlRoot const& value, const winrt::hstring& message)
{
    Controls::ContentDialog filesDialog;
    filesDialog.XamlRoot(value);
    filesDialog.Title(winrt::box_value(L"��ʾ"));
    filesDialog.Content(winrt::box_value(message));
    filesDialog.CloseButtonText(L"ȷ��");
    co_return co_await filesDialog.ShowAsync();
}