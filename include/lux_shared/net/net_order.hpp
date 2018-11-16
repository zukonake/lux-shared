#pragma once

#include <type_traits>
#include <lux_shared/int.hpp>
#include <lux_shared/vec.hpp>

template<typename T>
void net_order(T* dst, T const* src);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

template<SizeT n>
void net_order_n(U8* dst, U8 const* src);
template<typename T>
void net_order(T* dst, T const* src) {
    LUX_ASSERT(dst != src);
    static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value);
    net_order_n<sizeof(T)>((U8*)dst, (U8 const*)src);
}

template<>
inline void net_order_n<1>(U8* dst, U8 const* src)
{
    *dst = *src;
}

template<>
inline void net_order_n<2>(U8* dst, U8 const* src)
{
    dst[1] = src[0];
    dst[0] = src[1];
}

template<>
inline void net_order_n<4>(U8* dst, U8 const* src)
{
    dst[3] = src[0];
    dst[2] = src[1];
    dst[1] = src[2];
    dst[0] = src[3];
}

template<>
inline void net_order_n<8>(U8* dst, U8 const* src)
{
    dst[7] = src[0];
    dst[6] = src[1];
    dst[5] = src[2];
    dst[4] = src[3];
    dst[3] = src[4];
    dst[2] = src[5];
    dst[1] = src[6];
    dst[0] = src[7];
}

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

template<typename T>
void net_order(T* dst, T const* src) {
    *dst = *src;
}

#else
    #error "invalid byte order"
#endif
