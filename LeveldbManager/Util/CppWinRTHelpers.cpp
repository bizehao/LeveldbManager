#include "pch.h"

#include "CppWinRTHelpers.h"

bool utils::registerSparsePackage(winrt::hstring externalLocation, winrt::hstring sparsePkgPath) {
    winrt::Windows::Foundation::Uri externalUri{externalLocation};
    winrt::Windows::Foundation::Uri packageUri{sparsePkgPath};
    //fmt::print("exe Location {}", externalLocation);
    //fmt::print("msix Address {}", sparsePkgPath);

    winrt::Windows::Management::Deployment::PackageManager packageManager;
    winrt::Windows::Management::Deployment::AddPackageOptions options;
    options.ExternalLocationUri(externalUri);
    auto deploymentOperation = packageManager.AddPackageByUriAsync(packageUri, options);

    auto deployResult = deploymentOperation.get();
    if (deployResult) {
        //fmt::print("×¢²á³É¹¦");
        return true;

    } else {
        auto errorText = winrt::to_string(deployResult.ErrorText());
        //fmt::print("{}", errorText);
        //fmt::print("×¢²áÊ§°Ü");
        return false;
    }
}