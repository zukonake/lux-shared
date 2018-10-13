#pragma once

#include <algorithm>
#include <vector>

template<typename T>
class SparseDynArr {
    public:
    class Iter {
        public:
        Iter(T* ptr, SparseDynArr<T>& arr);
        Iter& operator++();
        bool operator!=(Iter const& other);
        T& operator*();
        private:
        T* ptr;
        SparseDynArr<T>& arr;
    };
    class CIter {
        public:
        CIter(T const* ptr, SparseDynArr<T> const& arr);
        CIter& operator++();
        bool operator!=(CIter const& other);
        T const& operator*();
        private:
        T const* ptr;
        SparseDynArr<T> const& arr;
    };
    friend class Iter;
    friend class CIter;

    template<typename ...Args>
    SizeT emplace(Args &&...args);
    void  erase(SizeT idx);

    void reserve(SizeT len);
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
    //@IMPROVE save space with pointers (implicit size, instead of duplication)
    std::vector<T>    data;
    std::vector<bool> slots;
};

template<typename T>
template<typename ...Args>
SizeT SparseDynArr<T>::emplace(Args &&...args) {
    SizeT idx = std::find(slots.cbegin(), slots.cend(), false) - slots.cbegin();
    if(idx == data.size()) {
        data.emplace_back(args...);
        slots.emplace_back(true);
    } else {
        new (data.data() + idx) T(args...);
        slots[idx] = true;
    }
    return idx;
}

template<typename T>
void SparseDynArr<T>::erase(SizeT idx) {
    LUX_ASSERT(idx < data.size());
    data[idx].~T();
    slots[idx] = false;
}

template<typename T>
void SparseDynArr<T>::reserve(SizeT len) {
    data.reserve(len);
    slots.reserve(len);
}

template<typename T>
void SparseDynArr<T>::shrink_to_fit() {
    data.shrink_to_fit();
    SizeT last_full_idx =
        std::find(slots.crbegin(), slots.crend(), true) - slots.crbegin();
    slots.resize(last_full_idx + 1);
    slots.shrink_to_fit();
}

template<typename T>
T& SparseDynArr<T>::operator[](SizeT idx) {
    LUX_ASSERT(idx < data.size());
    return data[idx];
}

template<typename T>
T const& SparseDynArr<T>::operator[](SizeT idx) const {
    LUX_ASSERT(idx < data.size());
    return data[idx];
}

template<typename T>
bool SparseDynArr<T>::contains(SizeT idx) const {
    if(idx >= data.size()) return false;
    return slots[idx];
}

template<typename T>
SizeT SparseDynArr<T>::size() const {
    SizeT size = 0;
    for(Uns i = 0; i < data.size(); ++i) {
        size += slots[i];
    }
    return size;
}

template<typename T>
typename SparseDynArr<T>::Iter SparseDynArr<T>::begin() {
    return {data.data(), *this};
}

template<typename T>
typename SparseDynArr<T>::CIter SparseDynArr<T>::cbegin() const {
    return {data.data(), *this};
}

template<typename T>
typename SparseDynArr<T>::Iter SparseDynArr<T>::end() {
    return {data.data() + data.size(), *this};
}

template<typename T>
typename SparseDynArr<T>::CIter SparseDynArr<T>::cend() const {
    return {data.data() + data.size(), *this};
}

template<typename T>
SparseDynArr<T>::Iter::Iter(T* ptr, SparseDynArr<T>& arr) :
    ptr(ptr),
    arr(arr) {

}

template<typename T>
typename SparseDynArr<T>::Iter& SparseDynArr<T>::Iter::operator++() {
    ++ptr;
    SizeT idx = ptr - arr.data.data();
    SizeT new_idx = std::find(arr.slots.begin() + idx,
                              arr.slots.end(), true) - arr.slots.begin();
    ptr = arr.data.data() + new_idx;
    return *this;
}

template<typename T>
bool SparseDynArr<T>::Iter::operator!=(Iter const& other) {
    return ptr != other.ptr;
}


template<typename T>
T& SparseDynArr<T>::Iter::operator*() {
    return *ptr;
}

template<typename T>
SparseDynArr<T>::CIter::CIter(T const* ptr, SparseDynArr<T> const& arr) :
    ptr(ptr),
    arr(arr) {

}

template<typename T>
typename SparseDynArr<T>::CIter& SparseDynArr<T>::CIter::operator++() {
    ++ptr;
    SizeT idx = ptr - arr.data.data();
    SizeT new_idx = std::find(arr.slots.cbegin() + idx,
                              arr.slots.cend(), true) - arr.slots.cbegin();
    ptr = arr.data.data() + new_idx;
    return *this;
}

template<typename T>
bool SparseDynArr<T>::CIter::operator!=(CIter const& other) {
    return ptr != other.ptr;
}

template<typename T>
T const& SparseDynArr<T>::CIter::operator*() {
    return *ptr;
}
