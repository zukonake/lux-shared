#pragma once

#include <array>
#include <vector>
#include <lux_shared/int.hpp>
#include <lux_shared/macro.hpp>

template<typename T>
struct Slice {
    Slice() = default;
    Slice(T*  beg, SizeT _len);
    template<typename That>
    explicit Slice(That const& that);
    template<typename ThatT>
    Slice(Slice<ThatT> const& that);
    Slice(std::vector<T> const& that);
    template<SizeT LEN>
    Slice(std::array<T, LEN> const& that);
    template<typename ThatT>
    Slice<T>& operator=(Slice<ThatT> const& that);
    template<typename That>
    Slice<T>& operator=(That const& that);

    template<typename That>
    explicit operator That() const;

    void set(T* beg, SizeT len);

    T const& operator[](SizeT idx) const;
    T      & operator[](SizeT idx);

    T*    beg;
    SizeT len;
};

template<typename T>
template<typename That>
Slice<T>::Slice(That const& that) {
    this->set((U8*)&that, sizeof(That));
}

template<typename T>
template<typename ThatT>
Slice<T>::Slice(Slice<ThatT> const& that) {
    this->set((U8*)that.beg, that.len * sizeof(ThatT));
}

template<typename T>
Slice<T>::Slice(std::vector<T> const& that) {
    this->set(that.data(), that.size());
}

template<typename T>
template<SizeT LEN>
Slice<T>::Slice(std::array<T, LEN> const& that) {
    this->set(that.data(), LEN);
}

template<typename T>
template<typename That>
Slice<T>& Slice<T>::operator=(That const& that) {
    this->set((U8*)&that, sizeof(That));
    return *this;
}

template<typename T>
template<typename ThatT>
Slice<T>& Slice<T>::operator=(Slice<ThatT> const& that) {
    this->set((U8*)that.beg, that.len * sizeof(ThatT));
    return *this;
}

template<typename T>
template<typename That>
Slice<T>::operator That() const {
    LUX_ASSERT(this->len <= sizeof(That));
    return *(That*)this->beg;
}

template<typename T>
void Slice<T>::set(T* beg, SizeT len) {
    this->beg = beg;
    this->len = len;
}

template<typename T>
T const& Slice<T>::operator[](SizeT idx) const {
    return this->beg[idx];
}

template<typename T>
T& Slice<T>::operator[](SizeT idx) {
    return this->beg[idx];
}
