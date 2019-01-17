#pragma once

#include <tuple>
//
#include <xxhash/xxhash.hpp>
//
#include <lux_shared/int.hpp>
#include <lux_shared/macro.hpp>

extern U64 random_seed;

//@TODO 32-bit support
template<typename... Args>
U64 lux_rand(Args const& ...args) {
    auto tuple = std::make_tuple(args...);
    return XXH64((const void*)&tuple, sizeof(tuple), random_seed);
}

template<typename... Args>
U64 lux_randm(U64 max, Args const& ...args) {
    return lux_rand(args...) % max;
}

template<typename... Args>
U64 lux_randmm(U64 min, U64 max, Args const& ...args) {
    LUX_ASSERT(min < max);
    return lux_randm(max - min, args...) + min;
}

template<typename... Args>
I64 lux_randsmm(I64 min, I64 max, Args const& ...args) {
    LUX_ASSERT(min < max);
    return (I64)lux_randm(max - min, args...) + min;
}

template<typename... Args>
F32 lux_randf(Args const& ...args) {
    constexpr SizeT max = 1 << 24;
    return (F32)lux_randm(max, args...) / (F32)(max - 1);
}

template<typename... Args>
F32 lux_randfmm(F32 min, F32 max, Args const& ...args) {
    LUX_ASSERT(min < max);
    return min + lux_randf(args...) * (max - min);
}
