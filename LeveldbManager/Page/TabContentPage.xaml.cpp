#include "pch.h"
#include "TabContentPage.xaml.h"
#if __has_include("TabContentPage.g.cpp")
#include "TabContentPage.g.cpp"
#endif
#include "Data/CommData.h"
#include "Util/Utils.h"
#include <nlohmann/json.hpp>
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include "Util/CppWinRTHelpers.h"
#include <winrt/Microsoft.Windows.ApplicationModel.Resources.h>
#include <Shlwapi.h> 

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::LeveldbManager::implementation {
    TabContentPage::TabContentPage() { 
        PropertyChanged([this](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs const& e) {
            if (e.PropertyName() == L"Value")
            {
                auto tStr = winrt::to_string(Value());
                int valueSize = tStr.size() * sizeof(char);
                ValueSize().Text(winrt::to_hstring(valueSize));
            }
        });
    }

    void TabContentPage::myButton_Click(IInspectable const&, RoutedEventArgs const&) {}
    void TabContentPage::OnNavigatedTo(Microsoft::UI::Xaml::Navigation::NavigationEventArgs e) {
        auto args = e.Parameter();
        _dbItem = args.as<DBItem>();
        _db = utils::as_self<ComLevelDBImpl>(_dbItem->Contact().Db())->DB();
        Key(_dbItem->Key());
        Value(_dbItem->Value());
        _realValue = _dbItem->Value();
    }

    void TabContentPage::ShowKey_LostFocus(winrt::Windows::Foundation::IInspectable const& sender,
                                           winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        // ShowKey().Text(Key());
    }

    void TabContentPage::ShowValue_LostFocus(winrt::Windows::Foundation::IInspectable const& sender,
                                             winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        // ShowValue().Text(Value());
    }

    void TabContentPage::Save_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        auto tValye = ShowValue().Text();
        Value(tValye);
        _realValue = tValye;
        auto pKey = winrt::to_string(Key());
        auto pValue = winrt::to_string(Value());
        auto result = _db->Put({}, pKey, pValue);
        assert(result.ok());
    }

    inline std::wstring get_module_folderpath(HMODULE mod = nullptr, const bool removeFilename = true) {
        wchar_t buffer[MAX_PATH + 1];
        DWORD actual_length = GetModuleFileNameW(mod, buffer, MAX_PATH);
        if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
            const DWORD long_path_length = 0xFFFF; // should be always enough
            std::wstring long_filename(long_path_length, L'\0');
            actual_length = GetModuleFileNameW(mod, long_filename.data(), long_path_length);
            PathRemoveFileSpec(long_filename.data());
            long_filename.resize(std::wcslen(long_filename.data()));
            long_filename.shrink_to_fit();
            return long_filename;
        }

        if (removeFilename) {
            PathRemoveFileSpec(buffer);
        }
        return {buffer, (UINT)lstrlenW(buffer)};
    }

    void TabContentPage::Flush_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        ShowValue().Text(Value());

        /*Microsoft::Windows::ApplicationModel::Resources::ResourceManager rm;
        auto mrmap = rm.MainResourceMap();
        int count = mrmap.ResourceCount();
        for (int i = 0; i < count; i++) {
            auto kv = mrmap.GetValueByIndex(i);
            auto kk = kv.Key();
            std::cout << "resourceKey: " << winrt::to_string(kk) << std::endl;
            auto vv = kv.Value();
            int a = 100;
        }*/
        /*auto ppp = get_module_folderpath();
        winrt::Windows::Management::Deployment::PackageManager manager;
        auto packages = manager.FindPackagesForUser({});
        for (const auto& package : packages) {
            auto packageName = package.Id().Name();
            std::cout << "resourceKey: " << winrt::to_string(packageName) << std::endl;
        }
        int a = 100;*/
    }

} // namespace winrt::LeveldbManager::implementation

void winrt::LeveldbManager::implementation::TabContentPage::ValueDisplayType_SelectionChanged(
    winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e) {
    if (MessageTip()) {
        MessageTip().IsOpen(false);
    }
    auto displayStr = ValueDisplayType().SelectedIndex();
    switch (displayStr) {
    case 0: // Text
        Value(_realValue);
        break;
    case 1: // Hex
    {
        auto stlStr = winrt::to_string(_realValue);
        std::stringstream sstemp;
        for (auto& c : stlStr) {
            auto binStr = utils::charToHex(c);
            sstemp << binStr;
        }
        auto temp = sstemp.str();
        Value(winrt::to_hstring(temp));
    } break;
    case 2: // Json
    {
        try {
            auto stlStr = winrt::to_string(_realValue);
            nlohmann::json j = nlohmann::json::parse(stlStr);
            auto jsonStr = j.dump(4);
            Value(winrt::to_hstring(jsonStr));
        } catch (std::exception e) {
            MessageTip().IsOpen(true);
            Value(_realValue);
        }
    } break;
    case 3: // Binary
    {
        auto stlStr = winrt::to_string(_realValue);
        std::stringstream sstemp;
        for (auto& c : stlStr) {
            auto binStr = utils::charToBinary(c);
            sstemp << binStr;
        }
        auto temp = sstemp.str();
        Value(winrt::to_hstring(temp));
    }

    break;
    }
}

void winrt::LeveldbManager::implementation::TabContentPage::DeleteKey_Click(winrt::Windows::Foundation::IInspectable const& sender,
                                                                                   winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
    //TODO:bzh
    /*auto temKey = winrt::to_string(Key());
    auto result = _db->Delete({}, temKey);
    assert(result.ok());
    auto mWindow = App::Window();
    mWindow->closeTab(_dbItem->Contact(), Key());
    uint32_t index = -1;
    _dbItem->Contact().KeyDatas().IndexOf(Key(), index);
    assert(index != -1);
    _dbItem->Contact().KeyDatas().RemoveAt(index);*/
}
