#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <net/tile_state.hpp>
#include <net/serializer.hpp>
#include <net/deserializer.hpp>
#include <common/entity.hpp>

namespace net
{

struct ServerData
{
    Vector<TileState> tiles;
    Vector<EntityPoint> entities;
    EntityPoint player_pos;
};

inline Serializer &operator<<(Serializer &in, ServerData const &v)
{
    in << (U32)v.tiles.size();
    for(auto const &tile : v.tiles) in << tile;
    in << (U32)v.entities.size();
    for(auto const &i : v.entities) in << i;
    in << v.player_pos;
    return in;
}

inline Deserializer &operator>>(Deserializer &out, ServerData &v)
{
    {
        U32 tiles_len;
        out >> tiles_len;
        v.tiles.reserve(tiles_len);
        for(SizeT i = 0; i < tiles_len; ++i)
        {
            v.tiles.emplace_back();
            out >> v.tiles.back();
        }
    }
    {
        U32 entities_len;
        out >> entities_len;
        v.entities.reserve(entities_len);
        for(SizeT i = 0; i < entities_len; ++i)
        {
            v.entities.emplace_back();
            out >> v.entities.back();
        }
    }
    out >> v.player_pos;
    return out;
}

}
