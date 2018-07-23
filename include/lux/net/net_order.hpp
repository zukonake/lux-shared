#pragma once

#include <cstring>
//
#include <lux/alias/scalar.hpp>

namespace net
{

inline void net_memcpy(U8 *dst, U8 *src, SizeT n)
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    U8 *end = src + n - 1;
    while(end >= src)
    {
        *(dst++) = *(end--);
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
    return (U16)((val & 0x00FF) << 8) |
                ((val & 0xFF00) >> 8);
}

template<>
inline U32 net_order(U32 val)
{
    return (U32)((val & 0x000000FF) << 24) |
                ((val & 0x0000FF00) <<  8) |
                ((val & 0x00FF0000) >>  8) |
                ((val & 0xFF000000) >> 24);
}

template<>
inline U64 net_order(U64 val)
{
    return (U64)((val & 0x00000000000000FF) << 56) |
                ((val & 0x000000000000FF00) << 40) |
                ((val & 0x0000000000FF0000) << 24) |
                ((val & 0x00000000FF000000) <<  8) |
                ((val & 0x000000FF00000000) >>  8) |
                ((val & 0x0000FF0000000000) >> 24) |
                ((val & 0x00FF000000000000) >> 40) |
                ((val & 0xFF00000000000000) >> 56);
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
