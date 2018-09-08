#pragma once

#include <lux/alias/vector.hpp>
#include <lux/net/server/geometry_update.hpp>
#include <lux/net/server/lightning_update.hpp>

namespace net::server
{

//TODO consider splitting into two structs
struct MapUpdates
{
    Vector<GeometryUpdate>  geometry_updates;
    Vector<LightningUpdate> lightning_updates;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::MapUpdates); }
