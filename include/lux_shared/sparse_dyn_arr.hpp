#pragma once

#include <algorithm>
#include <vector>
//
#include <lux_shared/memory.hpp>

template<typename T>
class SparseDynArr {
    public:
    struct Iter {
        public:
        Iter& operator++();
        bool operator!=(Iter const& other);
        T& operator*();

        SizeT idx;
        SparseDynArr<T>* arr;
    };
    struct CIter {
        public:
        CIter& operator++();
        bool operator!=(CIter const& other);
        T const& operator*();

        SizeT idx;
        SparseDynArr<T> const* arr;
    };
    friend class Iter;
    friend class CIter;

    ~SparseDynArr();

    template<typename ...Args>
    SizeT emplace(Args &&...args);
    void  erase(SizeT idx);

    void shrink_to_fit();

    T&       operator[](SizeT idx);
    T const& operator[](SizeT idx) const;

    bool  contains(SizeT idx) const;
    SizeT size() const;

    Iter   begin();
    CIter cbegin() const;
    Iter   end();
    CIter cend() const;
    private:
    std::vector<bool> slots;
    T*                data;
    SizeT             cap = 0;
};

template<typename T>
SparseDynArr<T>::~SparseDynArr() {
    if(cap > 0) {
        for(auto it = begin(); it != end(); ++it) {
            erase(it.idx);
        }
        lux_free<T>(data);
    }
}

template<typename T>
template<typename ...Args>
SizeT SparseDynArr<T>::emplace(Args &&...args) {
    SizeT idx = std::find(slots.cbegin(), slots.cend(), false) - slots.cbegin();
    if(idx == slots.size()) {
        if(cap < idx + 1) {
            if(cap == 0) {
                cap  = 1;
                data = lux_alloc<T>(cap);
            } else {
                cap *= 2;
                T* new_data = lux_alloc<T>(cap);
                for(auto it = begin(); it != end(); ++it) {
                    new (new_data + it.idx) T(std::move(*it));
                    (*it).~T();
                }
                lux_free<T>(data);
                data = new_data;
            }
        }
        slots.emplace_back(true);
    } else {
        slots[idx] = true;
    }
    new (data + idx) T(args...);
    return idx;
}

template<typename T>
void SparseDynArr<T>::erase(SizeT idx) {
    LUX_ASSERT(idx < slots.size());
    data[idx].~T();
    if(idx == slots.size() - 1) {
        slots.pop_back();
    }
    else slots[idx] = false;
}

template<typename T>
void SparseDynArr<T>::shrink_to_fit() {
    if(slots.size() == 0) {
        lux_free<T>(data);
        data = nullptr;
    } else {
        data = lux_realloc<T>(data, slots.size());
    }
    cap = slots.size();
    slots.shrink_to_fit();
}

template<typename T>
T& SparseDynArr<T>::operator[](SizeT idx) {
    LUX_ASSERT(idx < slots.size());
    return data[idx];
}

template<typename T>
T const& SparseDynArr<T>::operator[](SizeT idx) const {
    LUX_ASSERT(idx < slots.size());
    return data[idx];
}

template<typename T>
bool SparseDynArr<T>::contains(SizeT idx) const {
    if(idx >= slots.size()) return false;
    return slots[idx];
}

template<typename T>
SizeT SparseDynArr<T>::size() const {
    SizeT size = 0;
    for(Uns i = 0; i < slots.size(); ++i) {
        size += slots[i];
    }
    return size;
}

template<typename T>
typename SparseDynArr<T>::Iter SparseDynArr<T>::begin() {
    return {(SizeT)(std::find(slots.begin(),
                              slots.end(), true) - slots.begin()), this};
}

template<typename T>
typename SparseDynArr<T>::CIter SparseDynArr<T>::cbegin() const {
    return {(SizeT)(std::find(slots.cbegin(),
                              slots.cend(), true) - slots.cbegin()), this};
}

template<typename T>
typename SparseDynArr<T>::Iter SparseDynArr<T>::end() {
    return {slots.size(), this};
}

template<typename T>
typename SparseDynArr<T>::CIter SparseDynArr<T>::cend() const {
    return {slots.size(), this};
}

template<typename T>
typename SparseDynArr<T>::Iter& SparseDynArr<T>::Iter::operator++() {
    idx = std::find(arr->slots.begin() + idx + 1,
                    arr->slots.end(), true) - arr->slots.begin();
    return *this;
}

template<typename T>
bool SparseDynArr<T>::Iter::operator!=(Iter const& other) {
    return idx != other.idx;
}


template<typename T>
T& SparseDynArr<T>::Iter::operator*() {
    return (*arr)[idx];
}

template<typename T>
typename SparseDynArr<T>::CIter& SparseDynArr<T>::CIter::operator++() {
    idx = std::find(arr->slots.cbegin() + idx + 1,
                    arr->slots.cend(), true) - arr->slots.cbegin();
    return *this;
}

template<typename T>
bool SparseDynArr<T>::CIter::operator!=(CIter const& other) {
    return idx != other.idx;
}

template<typename T>
T const& SparseDynArr<T>::CIter::operator*() {
    return (*arr)[idx];
}
