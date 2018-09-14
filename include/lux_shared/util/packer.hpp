#pragma once

#include <lux_shared/common.hpp>

namespace util
{

template<typename T>
struct Packer
{
    SizeT operator()(T const &);
};

}
