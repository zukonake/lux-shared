#pragma once

#include <lux/common.hpp>

U8 constexpr NET_VERSION_MAJOR = 0;
U8 constexpr NET_VERSION_MINOR = 0;
U8 constexpr NET_VERSION_PATCH = 0;

Uns constexpr CHANNEL_NUM  = 3;
U8  constexpr INIT_CHANNEL   = 0x00;
U8  constexpr TICK_CHANNEL   = 0x01;
U8  constexpr SIGNAL_CHANNEL = 0x02;

Uns constexpr SERVER_NAME_LEN = 32;
Uns constexpr CLIENT_NAME_LEN = 16;
