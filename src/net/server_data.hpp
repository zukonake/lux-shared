#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <net/tile_state.hpp>

namespace net
{

struct ServerData
{
    Vector<TileState> tiles;

    static void   serialize(ServerData const &server_data, Vector<U8>       &bytes);
    static void deserialize(ServerData       &server_data, Vector<U8> const &bytes);
};

}
