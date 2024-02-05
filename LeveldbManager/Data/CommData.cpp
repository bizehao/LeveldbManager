#include "pch.h"
#include "CommData.h"

DBItem::DBItem(winrt::LeveldbManager::Contact contact, const winrt::hstring& key, const winrt::hstring& value)
    : _contact{contact}, _key{key}, _value{value} {}


winrt::hstring DBItem::Key() { return _key; }


winrt::hstring DBItem::Value() { return _value; }

winrt::LeveldbManager::Contact DBItem::Contact() { return _contact; }

