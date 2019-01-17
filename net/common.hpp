#pragma once

#include <enet/enet.h>
//
#include <lux_shared/common.hpp>

//@CONSIDER moving to server/client
U8 constexpr NET_VERSION_MAJOR = 0;
U8 constexpr NET_VERSION_MINOR = 0;
U8 constexpr NET_VERSION_PATCH = 0;

Uns constexpr CHANNEL_NUM  = 3;
U8  constexpr INIT_CHANNEL = 0x00;
U8  constexpr TICK_CHANNEL = 0x01;
U8  constexpr SGNL_CHANNEL = 0x02;

Uns constexpr SERVER_NAME_LEN = 32;
Uns constexpr CLIENT_NAME_LEN = 16;

inline U8* get_ip(ENetAddress const& addr) {
    static_assert(sizeof(addr.host) == 4);
    return (U8*)&addr.host;
}
