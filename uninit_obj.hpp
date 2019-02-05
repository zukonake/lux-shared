#pragma once

#include <type_traits>

template<typename T>
struct UninitObj {
    std::aligned_storage_t<sizeof(T), alignof(T)> data;

    template<typename... Args>
    void init(Args&& ...args) {
        new ((T*)&data) T(args...);
    }

    void deinit() {
        ((T*)&data)->~T();
    }

    T& operator*() const {
        return (T&)data;
    }

    T* operator->() const {
        return (T*)&data;
    }
};
