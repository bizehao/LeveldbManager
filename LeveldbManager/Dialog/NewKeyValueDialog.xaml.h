#pragma once

#include "NewKeyValueDialog.g.h"

namespace winrt::LeveldbManager::implementation
{
    struct NewKeyValueDialog : NewKeyValueDialogT<NewKeyValueDialog>
    {
        NewKeyValueDialog();

    };
}

namespace winrt::LeveldbManager::factory_implementation
{
    struct NewKeyValueDialog : NewKeyValueDialogT<NewKeyValueDialog, implementation::NewKeyValueDialog>
    {
    };
}
