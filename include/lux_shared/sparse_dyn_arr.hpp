#pragma once

#include <algorithm>
#include <vector>
//
#include <lux_shared/memory.hpp>

template<typename T, typename _Id = U32>
class SparseDynArr {
    public:
    typedef _Id Id;
    struct Iter {
        public:
        Iter& operator++();
        bool operator!=(Iter const& other);
        bool is_valid();
        T& operator*();
        T* operator->();
        T const& operator*() const;
        T const* operator->() const;
        void erase();

        SparseDynArr<T, Id>* arr;
        Id id;
    };
    friend class Iter;

    ~SparseDynArr();

    template<typename ...Args>
    Iter emplace(Args &&...args);
    void shrink_to_fit();
    SizeT size() const;

    Iter begin();
    Iter end();
    private:
    std::vector<bool> slots;
    T*                data;
    SizeT             cap = 0;
};

template<typename T, typename Id>
SparseDynArr<T, Id>::~SparseDynArr() {
    if(cap > 0) {
        for(auto it = begin(); it != end(); ++it) {
            it.erase();
        }
        lux_free<T>(data);
    }
}

template<typename T, typename Id>
template<typename ...Args>
typename SparseDynArr<T, Id>::Iter SparseDynArr<T, Id>::emplace(Args &&...args) {
    Id id = std::find(slots.cbegin(), slots.cend(), false) - slots.cbegin();
    if(id == slots.size()) {
        if(cap < id + 1u) {
            if(cap == 0) {
                cap  = 1;
                data = lux_alloc<T>(cap);
            } else {
                cap *= 2;
                T* new_data = lux_alloc<T>(cap);
                for(auto it = begin(); it != end(); ++it) {
                    new (new_data + it.id) T(std::move(*it));
                    it->~T();
                }
                lux_free<T>(data);
                data = new_data;
            }
        }
        slots.emplace_back(true);
    } else {
        slots[id] = true;
    }
    new (data + id) T(args...);
    return {this, id};
}

template<typename T, typename Id>
void SparseDynArr<T, Id>::shrink_to_fit() {
    if(slots.size() == 0) {
        lux_free<T>(data);
        data = nullptr;
    } else {
        T* new_data = lux_alloc<T>(slots.size());
        for(auto it = begin(); it != end(); ++it) {
            new (new_data + it.id) T(std::move(*it));
            (*it).~T();
        }
        lux_free<T>(data);
        data = new_data;
    }
    cap = slots.size();
    slots.shrink_to_fit();
}

template<typename T, typename Id>
SizeT SparseDynArr<T, Id>::size() const {
    SizeT size = 0;
    for(Uns i = 0; i < slots.size(); ++i) {
        size += slots[i];
    }
    return size;
}

template<typename T, typename Id>
typename SparseDynArr<T, Id>::Iter SparseDynArr<T, Id>::begin() {
    return {this,
            (Id)(std::find(slots.begin(), slots.end(), true) - slots.begin())};
}

template<typename T, typename Id>
typename SparseDynArr<T, Id>::Iter SparseDynArr<T, Id>::end() {
    return {this, (Id)slots.size()};
}

template<typename T, typename Id>
typename SparseDynArr<T, Id>::Iter& SparseDynArr<T, Id>::Iter::operator++() {
    id = std::find(arr->slots.begin() + id + 1,
                   arr->slots.end(), true) - arr->slots.begin();
    return *this;
}

template<typename T, typename Id>
bool SparseDynArr<T, Id>::Iter::operator!=(Iter const& other) {
    LUX_ASSERT(other.arr == arr);
    return id != other.id;
}

template<typename T, typename Id>
bool SparseDynArr<T, Id>::Iter::is_valid() {
    if(id >= arr->slots.size()) return false;
    return arr->slots[id];
}

template<typename T, typename Id>
T& SparseDynArr<T, Id>::Iter::operator*() {
    return arr->data[id];
}

template<typename T, typename Id>
T* SparseDynArr<T, Id>::Iter::operator->() {
    return &arr->data[id];
}

template<typename T, typename Id>
T const& SparseDynArr<T, Id>::Iter::operator*() const {
    return arr->data[id];
}

template<typename T, typename Id>
T const* SparseDynArr<T, Id>::Iter::operator->() const {
    return &arr->data[id];
}

template<typename T, typename Id>
void SparseDynArr<T, Id>::Iter::erase() {
    LUX_ASSERT(is_valid());
    arr->data[id].~T();
    if(id == arr->slots.size() - 1) {
        arr->slots.pop_back();
    }
    else arr->slots[id] = false;
}
