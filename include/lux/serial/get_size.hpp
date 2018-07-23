#pragma once

#include <lux/alias/scalar.hpp>

namespace serial
{

template<typename T>
SizeT get_size(T const &v)
{
    return sizeof(v);
}

}
