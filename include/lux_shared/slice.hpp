#pragma once

#include <lux_shared/common.hpp>

template<typename T>
struct Slice {
    Slice() = default;
    Slice(U8* beg, SizeT _len);
    template<typename That>
    explicit Slice(That const& that);
    template<typename ThatT>
    Slice(Slice<ThatT> const& that);
    template<typename ThatT>
    Slice<T>& operator=(Slice<ThatT> const& that);
    template<typename That>
    Slice<T>& operator=(That const& that);

    template<typename That>
    explicit operator That() const;

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
template<typename That>
Slice<T>::Slice(That const& that) {
    this->set((U8*)&that, sizeof(That));
}

template<typename T>
template<typename That>
Slice<T>& Slice<T>::operator=(That const& that) {
    this->set((U8*)&that, sizeof(That));
}

template<typename T>
template<typename That>
Slice<T>::operator That() const {
    LUX_ASSERT(this->len == sizeof(That));
    return *(That*)this->beg;
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
