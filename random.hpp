#pragma once

#include <tuple>
//
#include <xxhash/xxhash.hpp>
//
#include <lux_shared/int.hpp>
#include <lux_shared/macro.hpp>
#include <lux_shared/vec.hpp>
#include <lux_shared/math.hpp>

extern U64 random_seed;

#pragma pack(push, 1)

template<typename... Xs>
struct PackedTuple { };

template<typename X, typename... Xs>
struct PackedTuple<X, Xs...> : PackedTuple<Xs...> {
    PackedTuple(X _x, Xs const& ...xs) :
        PackedTuple<Xs...>(xs...)
    {
        x = _x;
    }
    X x;
};

#pragma pack(pop)

//@TODO 32-bit support
template<typename... Args>
U64 lux_rand(Args const& ...args) {
    PackedTuple<Args...> tuple(args...);
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
F32 lux_randfm(F32 max, Args const& ...args) {
    return lux_randf(args...) * max;
}

template<typename... Args>
F32 lux_randfmm(F32 min, F32 max, Args const& ...args) {
    //@TODO is this correct?
    LUX_ASSERT(min < max);
    return min + lux_randfm(max - min, args...);
}

template<typename... Args>
Vec3F lux_rand_norm(Args const& ...args) {
    //@TODO confirm uniform distribution
    F32 angle = lux_randfm(tau, args..., 0);
    F32 z     = s_norm(lux_randf(args..., 1));
    return {cos(angle), sin(angle), z};
}
