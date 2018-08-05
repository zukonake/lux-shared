#pragma once

#include <lux/alias/hash.hpp>

namespace net::server
{

struct Tile
{
    Hash db_hash;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Tile); }
