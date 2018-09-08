#pragma once

#include <lux/net/server/tick.hpp>
#include <lux/net/server/init.hpp>
#include <lux/net/server/conf.hpp>
#include <lux/net/server/msg.hpp>
#include <lux/net/server/map.hpp>
#include <lux/net/server/map_updates.hpp>

namespace net::server
{

struct Packet
{
    enum : U8
    {
        TICK        = 0x00,
        INIT        = 0x01,
        CONF        = 0x02,
        MSG         = 0x03,
        MAP         = 0x04,
        MAP_UPDATE  = 0x05,
    } type;
    Tick       tick;
    Init       init;
    Conf       conf;
    Msg        msg;
    Map        map;
    MapUpdates map_updates;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Packet); }

