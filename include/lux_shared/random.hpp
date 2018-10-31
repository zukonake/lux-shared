#pragma once

#include <tuple>
//
#include <xxhash/xxhash.h>
//
#include <lux_shared/int.hpp>

extern U64 random_seed;

//@TODO 32-bit support
template<typename... Args>
U64 lux_rand(Args const& ...args) {
    auto tuple = std::make_tuple(args...);
    return XXH64((const void*)&tuple, sizeof(tuple), random_seed);
}

template<typename... Args>
U64 lux_rands(U64 span, Args const& ...args) {
    return lux_rand(args...) % span;
}

template<typename... Args>
U64 lux_randms(U64 min, U64 span, Args const& ...args) {
    return lux_rands(span, args...) + min;
}

template<typename... Args>
F32 lux_randf(Args const& ...args) {
    constexpr SizeT max = 1 << 24;
    return (F32)lux_rands(max, args...) / (F32)(max - 1);
}
