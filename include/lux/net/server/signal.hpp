#pragma once

#include <lux/net/server/signal/conf.hpp>
#include <lux/net/server/signal/msg.hpp>
#include <lux/net/server/signal/map.hpp>

namespace net::server
{

struct Signal
{
    enum : U8
    {
        INIT = 0x00,
        CONF = 0x01,
        MSG  = 0x02,
        MAP  = 0x03,
    } type;
    signal::Conf conf;
    signal::Msg  msg;
    signal::Map  map;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Signal); }

