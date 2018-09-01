#pragma once

#include <cstring>
//
#include <lux/alias/scalar.hpp>

namespace net
{

inline void net_memcpy(U8 *dst, U8 const *src, SizeT n)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    for(SizeT i = 0; i < n; ++i) {
        *(dst + i) = *(src + (n - 1) - i);
    }
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    std::memcpy(dst, src, n);
#else
#error "invalid byte order"
#endif
}

template<typename T>
T net_order(T val);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

//TODO use BSWAP asm instruction?
template<>
inline U8 net_order(U8 val)
{
    return val;
}

template<>
inline U16 net_order(U16 val)
{
    return (U16)((val & (0xFFull <<  0)) << 8) |
                ((val & (0xFFull <<  8)) >> 8);
}

template<>
inline U32 net_order(U32 val)
{
    return (U32)((val & (0xFFull <<  0)) << 24) |
                ((val & (0xFFull <<  8)) <<  8) |
                ((val & (0xFFull << 16)) >>  8) |
                ((val & (0xFFull << 24)) >> 24);
}

template<>
inline U64 net_order(U64 val)
{
    return (U64)((val & (0xFFull <<  0)) << 56) |
                ((val & (0xFFull <<  8)) << 40) |
                ((val & (0xFFull << 16)) << 24) |
                ((val & (0xFFull << 24)) <<  8) |
                ((val & (0xFFull << 32)) >>  8) |
                ((val & (0xFFull << 40)) >> 24) |
                ((val & (0xFFull << 48)) >> 40) |
                ((val & (0xFFull << 56)) >> 56);
}

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

template<typename T>
T net_order(T val)
{
    return val;
}

#else
#error "invalid byte order"
#endif

}
