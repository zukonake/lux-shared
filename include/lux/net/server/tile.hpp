#pragma once

#include <lux/common/tile.hpp>

namespace net::server
{

struct Tile
{
    tile::Id id;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Tile); }
