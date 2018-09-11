#pragma once

#include <lux/net/server/conf.hpp>
#include <lux/net/server/msg.hpp>
#include <lux/net/server/map.hpp>
#include <lux/net/server/map_updates.hpp>

namespace net::server
{

struct Signal
{
    enum : U8
    {
        CONF        = 0x00,
        MSG         = 0x01,
        MAP         = 0x02,
        MAP_UPDATES = 0x03,
    } type;
    Conf       conf;
    Msg        msg;
    Map        map;
    MapUpdates map_updates;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Signal); }
