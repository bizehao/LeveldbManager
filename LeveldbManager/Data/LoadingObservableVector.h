#pragma once
#include "LoadingObservableVector.g.h"

namespace winrt::LeveldbManager::implementation
{
    struct LoadingObservableVector : LoadingObservableVectorT<LoadingObservableVector>
    {
        LoadingObservableVector();

        LoadingObservableVector(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> const& vec);

        void SetSupportIncrementalLoadingHandle(winrt::LeveldbManager::ISupportIncrementalLoadingHandle const& value);

        winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::IInspectable> First();
        winrt::Windows::Foundation::IInspectable GetAt(uint32_t index);
        uint32_t Size();
        winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Foundation::IInspectable> GetView();
        bool IndexOf(winrt::Windows::Foundation::IInspectable const& value, uint32_t& index);
        void SetAt(uint32_t index, winrt::Windows::Foundation::IInspectable const& value);
        void InsertAt(uint32_t index, winrt::Windows::Foundation::IInspectable const& value);
        void RemoveAt(uint32_t index);
        void Append(winrt::Windows::Foundation::IInspectable const& value);
        void RemoveAtEnd();
        void Clear();
        uint32_t GetMany(uint32_t startIndex, array_view<winrt::Windows::Foundation::IInspectable> items);
        void ReplaceAll(array_view<winrt::Windows::Foundation::IInspectable const> items);
        winrt::event_token VectorChanged(winrt::Windows::Foundation::Collections::VectorChangedEventHandler<winrt::Windows::Foundation::IInspectable> const& vhnd);
        void VectorChanged(winrt::event_token const& token) noexcept;
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Data::LoadMoreItemsResult> LoadMoreItemsAsync(uint32_t count);
        bool HasMoreItems();

    private:
        //IObservableVector
        Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> _observableVector;
        winrt::LeveldbManager::ISupportIncrementalLoadingHandle _supportIncrementalLoadingHandle;
        winrt::event<winrt::Windows::Foundation::Collections::VectorChangedEventHandler<winrt::Windows::Foundation::IInspectable>> _mVectorChangedEvent;
    };
} // namespace winrt::LeveldbManager::implementation
namespace winrt::LeveldbManager::factory_implementation
{
    struct LoadingObservableVector : LoadingObservableVectorT<LoadingObservableVector, implementation::LoadingObservableVector>
    {
    };
} // namespace winrt::LeveldbManager::factory_implementation
