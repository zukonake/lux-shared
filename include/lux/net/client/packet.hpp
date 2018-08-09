#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/net/register_net_functions.hpp>
#include <lux/net/client/tick.hpp>
#include <lux/net/client/conf.hpp>
#include <lux/net/client/init.hpp>

namespace net::client
{

struct Packet
{
    enum : U8
    {
        TICK = 0x00,
        CONF = 0x01,
        INIT = 0x02,
    } type;
    Tick tick;
    Conf conf;
    Init init;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Packet); }
