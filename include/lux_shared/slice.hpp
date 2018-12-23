#pragma once

#include <cstring>
//
#include <lux_shared/int.hpp>
#include <lux_shared/macro.hpp>

template<typename T>
struct Slice {
    constexpr Slice() = default;
    constexpr Slice(T*  beg, SizeT _len);
    template<typename ThatT>
    constexpr Slice(Slice<ThatT> const& that);
    constexpr Slice(Slice<const T> const& that);
    template<SizeT LEN>
    constexpr Slice(T (&that)[LEN]);
    template<typename ThatT>
    constexpr Slice<T>& operator=(Slice<ThatT> const& that);

    template<typename ThatT>
    constexpr void set(ThatT* beg, SizeT len);

    template<typename ThatT>
    Slice<T> cpy(Slice<ThatT> const& that);
    void     set(T const& val);

    constexpr T const& operator[](SizeT idx) const;
    constexpr T      & operator[](SizeT idx);

    Slice<T> operator+(SizeT v) const;
    Slice<T>& operator+=(SizeT v);
    bool operator==(Slice<T> const& that) const;

    T*    beg;
    SizeT len;
};

template<typename T>
constexpr Slice<T>::Slice(T* _beg, SizeT _len) :
    beg(_beg),
    len(_len) {

}

template<typename T>
template<typename ThatT>
constexpr Slice<T>::Slice(Slice<ThatT> const& that) {
    this->set(that.beg, that.len);
}

template<typename T>
constexpr Slice<T>::Slice(Slice<const T> const& that) {
    this->set(that.beg, that.len);
}

template<typename T>
template<SizeT LEN>
constexpr Slice<T>::Slice(T (&that)[LEN]) :
    beg(that),
    len(LEN) {

}

template<typename T>
template<typename ThatT>
constexpr Slice<T>& Slice<T>::operator=(Slice<ThatT> const& that) {
    this->set(that.beg, that.len);
    return *this;
}

template<typename T>
template<typename ThatT>
constexpr void Slice<T>::set(ThatT* beg, SizeT len) {
    this->beg = (T*)beg;
    this->len = len;
}

template<typename T>
template<typename ThatT>
Slice<T> Slice<T>::cpy(Slice<ThatT> const& that) {
    LUX_ASSERT(that.len <= len);
    std::memcpy(beg, that.beg, that.len);
    return *this + that.len;
}

//@TODO confusing name with previous func
template<typename T>
void Slice<T>::set(T const& val) {
    for(Uns i = 0; i < len; i++) beg[i] = val;
}

template<typename T>
constexpr T const& Slice<T>::operator[](SizeT idx) const {
    LUX_ASSERT(idx < len);
    return this->beg[idx];
}

template<typename T>
constexpr T& Slice<T>::operator[](SizeT idx) {
    LUX_ASSERT(idx < len);
    return this->beg[idx];
}

template<typename T>
Slice<T> Slice<T>::operator+(SizeT v) const {
    return {beg + v, len - v};
}

template<typename T>
Slice<T>& Slice<T>::operator+=(SizeT v) {
    beg += v;
    len -= v;
    return *this;
}

template<typename T>
bool Slice<T>::operator==(Slice<T> const& that) const {
    if(len != that.len) return false;
    for(Uns i = 0; i < len; i++) {
        if((*this)[i] != that[i]) return false;
    }
    return true;
}
