#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/net/register_net_functions.hpp>
#include <lux/net/client/tick.hpp>

namespace net::client
{

struct Packet
{
    enum : U8
    {
        TICK = 0x00,
    } type;
    Tick tick;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Packet); }
