#pragma once

#include <hstring.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <leveldb/db.h>
#include "ComLevelDB.h"
#include "Data/Contact.h"

using namespace winrt;

class DBItem : public winrt::implements<DBItem, winrt::Windows::Foundation::IStringable>
{
public:
    DBItem(winrt::LeveldbManager::Contact contact, const winrt::hstring& key, const winrt::hstring& value);

    winrt::hstring Key();
    winrt::hstring Value();
    winrt::LeveldbManager::Contact Contact();

    winrt::hstring ToString() { return L"DBItem"; }

private:
    winrt::hstring _key;
    winrt::hstring _value;
    winrt::LeveldbManager::Contact _contact;
};

template<typename T>
class NewLoadingObservableVector : public winrt::implements<NewLoadingObservableVector<T>,
                                                            winrt::Windows::Foundation::Collections::IIterable<T>,
                                                            winrt::Windows::Foundation::Collections::IVector<T>,
                                                            winrt::Windows::Foundation::Collections::IObservableVector<T>,
                                                            winrt::Microsoft::UI::Xaml::Data::ISupportIncrementalLoading>
{
public:
    NewLoadingObservableVector(const Windows::Foundation::Collections::IObservableVector<T>& obVec) :
        _observableVector{obVec}
    {
        auto ss = _observableVector.Size();
        int aa = 100;
    }

    winrt::Windows::Foundation::Collections::IIterator<T> First()
    {
        return _observableVector.First();
    }
    T GetAt(uint32_t index)
    {
        return _observableVector.GetAt(index);
    }
    uint32_t Size()
    {
        return _observableVector.Size();
    }
    winrt::Windows::Foundation::Collections::IVectorView<T> GetView()
    {
        return _observableVector.GetView();
    }
    bool IndexOf(T const& value, uint32_t& index)
    {
        return _observableVector.IndexOf(value, index);
    }
    void SetAt(uint32_t index, T const& value)
    {
        _observableVector.SetAt(index, value);
    }
    void InsertAt(uint32_t index, T const& value)
    {
        _observableVector.InsertAt(index, value);
    }
    void RemoveAt(uint32_t index)
    {
        _observableVector.RemoveAt(index);
    }
    void Append(T const& value)
    {
        _observableVector.Append(value);
    }
    void RemoveAtEnd()
    {
        _observableVector.RemoveAtEnd();
    }
    void Clear()
    {
        _observableVector.Clear();
    }
    uint32_t GetMany(uint32_t startIndex, array_view<T> items)
    {
        return _observableVector.GetMany(startIndex, items);
    }
    void ReplaceAll(array_view<T const> items)
    {
        _observableVector.ReplaceAll(items);
    }
    winrt::event_token VectorChanged(winrt::Windows::Foundation::Collections::VectorChangedEventHandler<T> const& vhnd)
    {
        return _observableVector.VectorChanged(vhnd);
    }
    void VectorChanged(winrt::event_token const& token) noexcept
    {
        _observableVector.VectorChanged(token);
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::UI::Xaml::Data::LoadMoreItemsResult> LoadMoreItemsAsync(uint32_t count)
    {
        for (int i = 0; i < 10; i++)
        {
            _observableVector.Append(winrt::to_hstring(i));
        }
        co_return winrt::Microsoft::UI::Xaml::Data::LoadMoreItemsResult{0};
    }
    bool HasMoreItems()
    {
        return true;
    }

    Windows::Foundation::Collections::IObservableVector<T> _observableVector;
};