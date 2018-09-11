#pragma once

#include <lux/alias/scalar.hpp>

namespace net
{

typedef U32 Ip;
typedef U16 Port;

constexpr U8 TICK_CHANNEL   = 0x00;
constexpr U8 SIGNAL_CHANNEL = 0x01;
constexpr U8 INIT_CHANNEL   = 0x02;
constexpr U8 CHANNEL_NUM    = 3;

}
