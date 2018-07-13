#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <net/tile_state.hpp>
#include <net/serializer.hpp>
#include <net/deserializer.hpp>

namespace net
{

struct ServerData
{
    Vector<TileState> tiles;
};

inline Serializer &operator<<(Serializer &in, ServerData const &v)
{
    for(auto const &tile : v.tiles)
    {
        in << tile;
    }
    return in;
}

inline Deserializer &operator>>(Deserializer &out, ServerData &v)
{
    const SizeT tile_num = out.get_size() / sizeof(TileState);
    v.tiles.reserve(tile_num);
    for(SizeT i = 0; i < tile_num; ++i)
    {
        v.tiles.emplace_back();
        out >> v.tiles.back();
    }
    return out;
}

}
