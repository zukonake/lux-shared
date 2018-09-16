#pragma once

#include <lux_shared/int.hpp>
#include <lux_shared/vec.hpp>

template<typename T>
T net_order(T const& val);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

template<>
inline U8 net_order(U8 const& val)
{
    return val;
}

template<>
inline U16 net_order(U16 const& val)
{
    return (U16)((val & (0xFFull <<  0)) << 8) |
                ((val & (0xFFull <<  8)) >> 8);
}

template<>
inline U32 net_order(U32 const& val)
{
    return (U32)((val & (0xFFull <<  0)) << 24) |
                ((val & (0xFFull <<  8)) <<  8) |
                ((val & (0xFFull << 16)) >>  8) |
                ((val & (0xFFull << 24)) >> 24);
}

template<>
inline U64 net_order(U64 const& val)
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

template<> inline bool net_order(bool const& val) {
    return net_order<U8>(*(U8*)&val);
}

template<> inline I8  net_order(I8  const& val) {
    return net_order<U8 >(*(U8* )&val);
}

template<> inline I16 net_order(I16 const& val) {
    return net_order<U16>(*(U16*)&val);
}

template<> inline I32 net_order(I32 const& val) {
    return net_order<U32>(*(U32*)&val);
}

template<> inline I64 net_order(I64 const& val) {
    return net_order<U64>(*(U64*)&val);
}

template<> inline F32 net_order(F32 const& val) {
    return net_order<U32>(*(U32*)&val);
}

template<> inline F64 net_order(F64 const& val) {
    return net_order<U64>(*(U64*)&val);
}

template<typename T>
inline Vec2<T> net_order(Vec2<T> const& val) {
    return Vec2<T> { net_order<T>(val.x), net_order<T>(val.y) };
}

template<typename T>
inline Vec3<T> net_order(Vec3<T> const& val) {
    return Vec3<T> { net_order<T>(val.x),
                     net_order<T>(val.y),
                     net_order<T>(val.z) };
}

template<typename T>
inline Vec4<T> net_order(Vec4<T> const& val) {
    return Vec4<T> { net_order<T>(val.x),
                     net_order<T>(val.y),
                     net_order<T>(val.z),
                     net_order<T>(val.w) };
}

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

template<typename T>
inline T net_order(T const& val) {
    return val;
}

#else
    #error "invalid byte order"
#endif
