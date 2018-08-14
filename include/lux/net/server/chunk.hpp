#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/common/map.hpp>
#include <lux/common/tile.hpp>

namespace net::server
{

struct Chunk
{
    ChkPos pos;
    Array<tile::Id, CHK_VOLUME> tile_ids;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Chunk); }

