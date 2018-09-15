#pragma once

#include <lux_shared/common.hpp>

template<typename T>
struct Slice {
    Slice() = default;
    Slice(U8* beg, SizeT _len);
    template<typename ThatT>
    Slice(Slice<ThatT> const& that);
    template<typename ThatT>
    Slice<T>& operator=(Slice<ThatT> const& that);

    void set(U8* beg, SizeT len);

    T const& operator[](SizeT idx) const;
    T      & operator[](SizeT idx);

    T*    beg;
    SizeT len;
};

template<typename T>
Slice<T>::Slice(U8* beg, SizeT len) {
    this->set(beg, len);
}

template<typename T>
template<typename ThatT>
Slice<T>::Slice(Slice<ThatT> const& that) {
    this->set((U8*)that.beg, that.len * sizeof(ThatT));
}

template<typename T>
template<typename ThatT>
Slice<T>& Slice<T>::operator=(Slice<ThatT> const& that) {
    this->set((U8*)that.beg, that.len * sizeof(ThatT));
    return *this;
}

template<>
void Slice<U8>::set(U8* beg, SizeT len) {
    this->beg = beg;
    this->len = len;
}

template<typename T>
void Slice<T>::set(U8* beg, SizeT len) {
    this->beg = (T*)beg;
    this->len = len / sizeof(T);
}

template<typename T>
T const& Slice<T>::operator[](SizeT idx) const {
    return this->beg[idx];
}

template<typename T>
T& Slice<T>::operator[](SizeT idx) {
    return this->beg[idx];
}
