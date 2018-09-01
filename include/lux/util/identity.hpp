#pragma once

#include <lux/alias/scalar.hpp>

namespace util
{

template<typename T>
struct Identity
{
    SizeT operator()(T const &v) {
        return static_cast<SizeT>(v);
    }
};

}
