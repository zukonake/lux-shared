#pragma once

#include <cstdlib>
//
#include <lux/util/log.hpp>

#define LUX_LOG(prefix, lvl, fmt, ...) \
    util::log(prefix, util::lvl, fmt __VA_OPT__(,) __VA_ARGS__);

#define LUX_TRACE(fmt, ...) \
    util::log("LUX_TRACE", util::TRACE, fmt __VA_OPT(,) __VA_ARGS__);

#define LUX_NO_COPY(ident) \
    ident(ident const &) = delete; \
    ident &operator=(ident const &) = delete;

#define LUX_MOVEABLE(ident) \
    ident(ident &&) = default; \
    ident &operator=(ident &&) = default;
