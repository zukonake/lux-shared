#pragma once

#include <cstdlib>
//
#include <lux/util/log.hpp>

namespace lux
{

template<typename ...Args>
inline void error(const char *prefix, const char *fmt, Args &&...args)
{
    util::log(prefix, util::CRITICAL, fmt, args...);
    std::quick_exit(EXIT_FAILURE);
}

}
