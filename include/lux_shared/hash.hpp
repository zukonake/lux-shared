#pragma once

#include <cstddef>
#include <type_traits>
//
#include <xxhash/xxhash.hpp>
//
#include <lux_shared/int.hpp>
#include <lux_shared/slice.hpp>
#include <lux_shared/dyn_arr.hpp>

template<typename V>
struct LuxHash {
    std::size_t operator()(V const& v) const {
        static_assert(std::is_arithmetic<V>::value);
        return XXH64((const void*)&v, sizeof(V), 0);
    }
};

template<typename T>
struct LuxHash<Slice<T>> {
    std::size_t operator()(Slice<T> const& v) const {
        return XXH64((const void*)v.beg, v.len * sizeof(T), 0);
    }
};

template<typename T>
struct LuxHash<DynArr<T>> {
    std::size_t operator()(DynArr<T> const& v) const {
        return LuxHash<Slice<T>>()((Slice<T>)v);
    }
};
