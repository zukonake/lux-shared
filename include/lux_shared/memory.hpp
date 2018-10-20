#pragma once

#include <cstdlib>
//
#include <lux_shared/common.hpp>

template<typename T>
inline T* lux_alloc(SizeT sz) {
    LUX_ASSERT(sz != 0);
    T* data = (T*)std::malloc(sizeof(T) * sz);
    if(data == nullptr) {
        LUX_PANIC("failed to allocate block of %zux%zuB", sizeof(T), sz);
    }
    return data;
}

template<typename T>
inline T* lux_realloc(T* ptr, SizeT sz) {
    LUX_ASSERT(sz != 0);
    T* data = (T*)std::realloc(ptr, sizeof(T) * sz);
    if(data == nullptr) {
        LUX_PANIC("failed to re-allocate block of %zux%zuB", sizeof(T), sz);
    }
    return data;
}

template<typename T>
inline void lux_free(T* ptr) {
    std::free(ptr);
}
