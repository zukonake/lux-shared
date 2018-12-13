#pragma once

#include <initializer_list>
//
#include <lux_shared/slice.hpp>

template<typename T>
class DynArr : public Slice<T> {
    public:
    DynArr();
    DynArr(std::initializer_list<T> init);
    DynArr(SizeT cap);
    template<typename ThatT>
    DynArr(Slice<ThatT> const& that);
    DynArr(DynArr<T> const& that);
    DynArr(DynArr<T>&& that);
    ~DynArr();

    using Slice<T>::operator==;
    template<typename ThatT>
    DynArr<T>& operator=(Slice<ThatT> const& that);
    DynArr<T>& operator=(DynArr<T> const& that);
    DynArr<T>& operator=(DynArr<T>&& that);
    T& operator[](SizeT idx);
    T const& operator[](SizeT idx) const;

    template<typename ...Args>
    T& emplace(Args&& ...args);
    T& push(T&& val);
    T& last();
    void erase(SizeT idx);
    T* begin() const;
    T* end() const;

    void resize(SizeT new_sz);
    void clear();
    void shrink_to_fit();
    void reserve_at_least(SizeT new_cap);
    void reserve_exactly(SizeT new_cap);
    void dealloc_all();
    SizeT  cap;
    SizeT& len = Slice<T>::len;
    T*&    beg = Slice<T>::beg;
};

template<typename T>
DynArr<T>::DynArr() {
    len = 0;
    cap = 0;
    ///doing this only because valgrind shows false positives in begin and end
    beg = nullptr;
}

template<typename T>
DynArr<T>::DynArr(std::initializer_list<T> init) {
    len = 0;
    cap = 0;
    reserve_exactly(init.size());
    for(auto&& x : init) {
        emplace(x);
    }
}

template<typename T>
DynArr<T>::DynArr(SizeT _cap) {
    len = 0;
    cap = 0;
    reserve_exactly(_cap);
    while(len < _cap) emplace();
}

template<typename T>
template<typename ThatT>
DynArr<T>::DynArr(Slice<ThatT> const& that) {
    len = 0;
    cap = 0;
    *this = that;
}

template<typename T>
DynArr<T>::DynArr(DynArr<T> const& that) :
    Slice<T>() {
    cap = 0;
    len = 0;
    reserve_exactly(that.len);
    while(len < that.len) {
        emplace(that.beg[len]);
    }
}

template<typename T>
DynArr<T>::DynArr(DynArr<T>&& that) {
    cap = 0;
    len = 0;
    *this = std::move(that);
}

template<typename T>
DynArr<T>::~DynArr() {
    dealloc_all();
}

template<typename T>
template<typename ThatT>
DynArr<T>& DynArr<T>::operator=(Slice<ThatT> const& that) {
    len = that.len;
    reserve_exactly(len);
    for(Uns i = 0; i < len; i++) {
        (*this)[i] = that[i];
    }
    return *this;
}

template<typename T>
DynArr<T>& DynArr<T>::operator=(DynArr<T> const& that) {
    return *this = (Slice<T>)that;
}

template<typename T>
DynArr<T>& DynArr<T>::operator=(DynArr<T>&& that) {
    dealloc_all();
    beg = that.beg;
    len = that.len;
    cap = that.cap;
    that.len = 0;
    that.cap = 0;
    return *this;
}

template<typename T>
T& DynArr<T>::operator[](SizeT idx) {
    LUX_ASSERT(idx < len);
    return beg[idx];
}

template<typename T>
T const& DynArr<T>::operator[](SizeT idx) const {
    LUX_ASSERT(idx < len);
    return beg[idx];
}

template<typename T>
template<typename ...Args>
T& DynArr<T>::emplace(Args&& ...args) {
    if(len >= cap) {
        reserve_at_least(len + 1);
    }
    new (beg + len) T(args...);
    len++;
    return last();
}

template<typename T>
T& DynArr<T>::push(T&& val) {
    if(len >= cap) {
        reserve_at_least(len + 1);
    }
    new (beg + len) T(std::move(val));
    len++;
    return last();
}

template<typename T>
T& DynArr<T>::last() {
    LUX_ASSERT(len > 0);
    return beg[len - 1];
}

template<typename T>
void DynArr<T>::erase(SizeT idx) {
    LUX_ASSERT(len != 0);
    LUX_ASSERT(idx < len);
    beg[idx].~T();
    for(Uns i = idx + 1; i < len; i++) {
        new (beg + i - 1) T(std::move(beg[i]));
        beg[i].~T();
    }
    len--;
}

template<typename T>
T* DynArr<T>::begin() const {
    return beg;
}

template<typename T>
T* DynArr<T>::end() const {
    return beg + len;
}

template<typename T>
void DynArr<T>::resize(SizeT new_sz) {
    reserve_at_least(new_sz);
    while(len < new_sz) {
        new (beg + len) T();
        len++;
    }
    while(len > new_sz) {
        len--;
        beg[len].~T();
    }
}

template<typename T>
void DynArr<T>::clear() {
    while(len > 0) erase(len - 1);
}

template<typename T>
void DynArr<T>::shrink_to_fit() {
    reserve_exactly(len);
}

template<typename T>
void DynArr<T>::reserve_at_least(SizeT new_cap) {
    SizeT temp = cap == 0 ? 1 : cap;
    while(temp < new_cap) {
        temp *= 2;
    }
    reserve_exactly(temp);
}

template<typename T>
void DynArr<T>::reserve_exactly(SizeT new_cap)
{
    if(cap == new_cap) return;
    if(new_cap == 0) {
        dealloc_all();
    } else if(cap == 0) {
        beg = lux_alloc<T>(new_cap);
        cap = new_cap;
    } else {
        T* new_beg = lux_alloc<T>(new_cap);
        for(Uns i = 0; i < len; i++) {
            new (new_beg + i) T(std::move(beg[i]));
            beg[i].~T();
        }
        lux_free<T>(beg);
        beg = new_beg;
        cap = new_cap;
    }
}

template<typename T>
void DynArr<T>::dealloc_all() {
    if(cap == 0) return;
    clear();
    lux_free<T>(beg);
    cap = 0;
}
