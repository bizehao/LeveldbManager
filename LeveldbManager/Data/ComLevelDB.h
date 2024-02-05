#pragma once
#include <hstring.h>
#include <winrt/Windows.Foundation.h>
#include <leveldb/db.h>

struct ComLevelDBImpl;

using ComLevelDB = winrt::com_ptr<ComLevelDBImpl>;

struct ComLevelDBImpl : winrt::implements<ComLevelDBImpl, winrt::Windows::Foundation::IClosable, winrt::Windows::Foundation::IStringable> {
    ComLevelDBImpl(leveldb::DB* db) : _db{db} {}
    winrt::hstring ToString() { return L"ComLevelDB"; }
    void Close() { delete _db; }
    leveldb::DB* DB() { return _db; }

private:
    leveldb::DB* _db;
};

