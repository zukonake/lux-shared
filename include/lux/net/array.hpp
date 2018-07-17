#pragma once

#include <lux/alias/scalar.hpp>

namespace net
{

template<typename T>
struct Array
{
    U64 len;
    T  *val;
};

}
