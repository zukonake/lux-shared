#pragma once

#include <cstddef>
#include <cstring>
#include <type_traits>
//
#include <xxhash/xxhash.h>
//
#include <lux_shared/int.hpp>
#include <lux_shared/string.hpp>

template<typename V>
struct LuxHash {
    std::size_t operator()(V const& v) const {
        static_assert(std::is_arithmetic<V>::value);
        return XXH64((const void*)&v, sizeof(V), 0);
    }
};

template<>
struct LuxHash<SttStr> {
    std::size_t operator()(SttStr const& v) const {
        return XXH64((const void*)v, std::strlen(v), 0);
    }
};

template<>
struct LuxHash<DynStr> {
    std::size_t operator()(DynStr const& v) const {
        return XXH64((const void*)v.data(), v.size(), 0);
    }
};
