#pragma once

#include <lux_shared/int.hpp>

template<SizeT _len>
class BitArr {
    public:
    typedef Uns Raw;
    static constexpr SizeT len = _len;
    static constexpr SizeT raw_len = (len + sizeof(Raw) - 1) / sizeof(Raw);
    struct Ref {
        Ref& operator=(bool v);
        operator bool() const;
        BitArr<len>& arr;
        SizeT idx;
    };

    Ref  operator[](SizeT idx);
    bool operator[](SizeT idx) const;

    Raw raw_data[raw_len];
};

template<SizeT _len>
typename BitArr<_len>::Ref& BitArr<_len>::Ref::operator=(bool v) {
    SizeT bit_idx = idx % sizeof(Raw);
    arr.raw_data[idx / sizeof(Raw)] &= ~((Raw)(1 << bit_idx));
    arr.raw_data[idx / sizeof(Raw)] |= v << bit_idx;
    return *this;
}

template<SizeT _len>
BitArr<_len>::Ref::operator bool() const {
    return ((BitArr<len> const&)arr)[idx];
}

template<SizeT _len>
typename BitArr<_len>::Ref BitArr<_len>::operator[](SizeT idx) {
    return {*this, idx};
}

template<SizeT _len>
bool BitArr<_len>::operator[](SizeT idx) const { 
    SizeT bit_idx = idx % sizeof(Raw);
    return (raw_data[idx / sizeof(Raw)] & (1 << bit_idx)) >> bit_idx;
}
