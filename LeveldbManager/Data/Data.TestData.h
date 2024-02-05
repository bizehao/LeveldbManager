#pragma once
#include "Data.TestData.g.h"

namespace winrt::Data::implementation
{
    struct TestData : TestDataT<TestData>
    {
        TestData() = default;

        void Say();
    };
}
namespace winrt::Data::factory_implementation
{
    struct TestData : TestDataT<TestData, implementation::TestData>
    {
    };
}
