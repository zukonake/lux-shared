#pragma once

#include <enet/enet.h>
//
#include <lux_shared/common.hpp>

U8 constexpr NET_VERSION_MAJOR = 0;
U8 constexpr NET_VERSION_MINOR = 0;
U8 constexpr NET_VERSION_PATCH = 0;

Uns constexpr CHANNEL_NUM  = 3;
U8  constexpr INIT_CHANNEL   = 0x00;
U8  constexpr TICK_CHANNEL   = 0x01;
U8  constexpr SIGNAL_CHANNEL = 0x02;

Uns constexpr SERVER_NAME_LEN = 32;
Uns constexpr CLIENT_NAME_LEN = 16;

inline U8* get_ip(ENetAddress const& addr) {
    static_assert(sizeof(addr.host) == 4);
    return (U8*)&addr.host;
}

template<typename T>
T net_order(T val);

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

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

template<> inline bool net_order(bool val) { return net_order<U8>(*(U8*)&val); }
template<> inline I8  net_order(I8  val) { return net_order<U8 >(*(U8* )&val); }
template<> inline I16 net_order(I16 val) { return net_order<U16>(*(U16*)&val); }
template<> inline I32 net_order(I32 val) { return net_order<U32>(*(U32*)&val); }
template<> inline I64 net_order(I64 val) { return net_order<U64>(*(U64*)&val); }
template<> inline F32 net_order(F32 val) { return net_order<F32>(*(F32*)&val); }
template<> inline F64 net_order(F64 val) { return net_order<F64>(*(F64*)&val); }

#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

template<typename T>
inline T net_order(T val) {
    return val;
}

#else
    #error "invalid byte order"
#endif
