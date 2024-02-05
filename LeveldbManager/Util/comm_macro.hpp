#pragma once

//init wil::single_threaded_notifying_property<double>
#define ORIGIN_INIT(NAME, ...) &m_propertyChanged, *this, L"" #NAME __VA_OPT__(,) __VA_ARGS__
