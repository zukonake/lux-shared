#pragma once

#include <algorithm>
#include <vector>

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
    return {data.size(), this};
}

template<typename T>
typename SparseDynArr<T>::CIter SparseDynArr<T>::cend() const {
    return {data.size(), this};
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
