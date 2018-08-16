#pragma once

#include <lux/alias/scalar.hpp>

namespace util
{

template<typename T>
struct Packer
{
    SizeT operator()(T const &);
};

}
