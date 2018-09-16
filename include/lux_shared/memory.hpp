#pragma once

#include <cstdlib>
//
#include <lux_shared/common.hpp>

template<typename T>
inline T* lux_alloc(SizeT sz) {
    LUX_ASSERT(sz != 0);
    return (T*) std::malloc(sizeof(T) * sz);
}

template<typename T>
inline T* lux_realloc(T* ptr, SizeT sz) {
    LUX_ASSERT(sz != 0);
    return (T*) std::realloc(ptr, sizeof(T) * sz);
}

template<typename T>
inline void lux_free(T* ptr) {
    std::free(ptr);
}
