#include "pch.h"
#include "LoadingObservableVector.h"
#include "LoadingObservableVector.g.cpp"

namespace winrt::LeveldbManager::implementation
{
    struct MyVectorChangedEventArgs : implements<MyVectorChangedEventArgs, Windows::Foundation::Collections::IVectorChangedEventArgs>
    {
        MyVectorChangedEventArgs(Windows::Foundation::Collections::CollectionChange const change, uint32_t const index) :
            m_change{change},
            m_index{index}
        {
        }

        Windows::Foundation::Collections::CollectionChange CollectionChange() const
        {
            return m_change;
        }

        uint32_t Index() const
        {
            return m_index;
        }

    private:
        Windows::Foundation::Collections::CollectionChange const m_change;
        uint32_t const m_index;
    };

    LoadingObservableVector::LoadingObservableVector() :
        _observableVector{winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>()}
    {
    }

    LoadingObservableVector::LoadingObservableVector(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> const& vec) :
        _observableVector{vec}
    {
    }

    void LoadingObservableVector::SetSupportIncrementalLoadingHandle(winrt::LeveldbManager::ISupportIncrementalLoadingHandle const& value)
    {
        _supportIncrementalLoadingHandle = value;
    }

    winrt::Windows::Foundation::Collections::IIterator<winrt::Windows::Foundation::IInspectable> LoadingObservableVector::First()
    {
        return _observableVector.First();
    }
    winrt::Windows::Foundation::IInspectable LoadingObservableVector::GetAt(uint32_t index)
    {
        return _observableVector.GetAt(index);
    }
    uint32_t LoadingObservableVector::Size()
    {
        return _observableVector.Size();
    }
    winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Foundation::IInspectable> LoadingObservableVector::GetView()
    {
        return _observableVector.GetView();
    }
    bool LoadingObservableVector::IndexOf(winrt::Windows::Foundation::IInspectable const& value, uint32_t& index)
    {
        return _observableVector.IndexOf(value, index);
    }
    void LoadingObservableVector::SetAt(uint32_t index, winrt::Windows::Foundation::IInspectable const& value)
    {
        _observableVector.SetAt(index, value);
    }
    void LoadingObservableVector::InsertAt(uint32_t index, winrt::Windows::Foundation::IInspectable const& value)
    {
        _observableVector.InsertAt(index, value);
    }
    void LoadingObservableVector::RemoveAt(uint32_t index)
    {
        _observableVector.RemoveAt(index);
    }
    void LoadingObservableVector::Append(winrt::Windows::Foundation::IInspectable const& value)
    {
        _observableVector.Append(value);
    }
    void LoadingObservableVector::RemoveAtEnd()
    {
        _observableVector.RemoveAtEnd();
    }
    void LoadingObservableVector::Clear()
    {
        _observableVector.Clear();
    }
    uint32_t LoadingObservableVector::GetMany(uint32_t startIndex, array_view<winrt::Windows::Foundation::IInspectable> items)
    {
        return _observableVector.GetMany(startIndex, items);
    }
    void LoadingObservableVector::ReplaceAll(array_view<winrt::Windows::Foundation::IInspectable const> items)
    {
        _observableVector.ReplaceAll(items);
    }
    winrt::event_token LoadingObservableVector::VectorChanged(winrt::Windows::Foundation::Collections::VectorChangedEventHandler<winrt::Windows::Foundation::IInspectable> const& vhnd)
    {
        return _mVectorChangedEvent.add(vhnd);
        //return _observableVector.VectorChanged(vhnd);
    }
    void LoadingObservableVector::VectorChanged(winrt::event_token const& token) noexcept
    {
        //_observableVector.VectorChanged(token);
        _mVectorChangedEvent.remove(token);
    }
    static int iivv = 0;
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Data::LoadMoreItemsResult> LoadingObservableVector::LoadMoreItemsAsync(uint32_t count)
    {
        auto pp = _observableVector.Size();
        uint32_t rstCount = 0;
        if (_supportIncrementalLoadingHandle)
        {
            auto vec = co_await _supportIncrementalLoadingHandle.LoadMoreItemsAsync(count);
            rstCount = vec.Size();
            for (uint32_t i = 0; i < vec.Size(); i++)
            {
                _observableVector.Append(vec.GetAt(i));
                _mVectorChangedEvent(*this, winrt::make<MyVectorChangedEventArgs>(Windows::Foundation::Collections::CollectionChange::ItemInserted, _observableVector.Size() - 1));
            }
        }
        co_return winrt::Microsoft::UI::Xaml::Data::LoadMoreItemsResult{rstCount};
    }
    bool LoadingObservableVector::HasMoreItems()
    {
        if (_supportIncrementalLoadingHandle)
        {
            return _supportIncrementalLoadingHandle.HasMoreItems();
        }
        else {
            return false;
        }
    }
} // namespace winrt::LeveldbManager::implementation
