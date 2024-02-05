#pragma once

#include "NewDbDialog.g.h"

namespace winrt::LeveldbManager::implementation
{
    struct NewDbDialog : NewDbDialogT<NewDbDialog>
    {
        NewDbDialog();

    winrt::Windows::Foundation::IAsyncAction Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::LeveldbManager::factory_implementation
{
    struct NewDbDialog : NewDbDialogT<NewDbDialog, implementation::NewDbDialog>
    {
    };
}
