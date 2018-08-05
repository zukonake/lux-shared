#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/common/chunk.hpp>
#include <lux/net/server/tile.hpp>

namespace net::server
{

struct Chunk
{
    chunk::Pos pos;
    Array<Tile, chunk::TILE_SIZE> tiles;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Chunk); }

