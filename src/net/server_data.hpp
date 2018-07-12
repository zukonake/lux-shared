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

template<>
inline void Serializer::push<ServerData>(ServerData const &val)
{
    for(auto const &i : val.tiles)
    {
        push<TileState>(i);
    }
}

template<>
inline void Deserializer::pop<ServerData>(ServerData &val)
{
    assert(val.tiles.size() == 0);
    assert((get_size() % sizeof(TileState)) == 0);

    const SizeT tile_num = get_size() / sizeof(TileState);
    val.tiles.reserve(tile_num);
    for(SizeT i = 0; i < tile_num; ++i)
    {
        val.tiles.emplace_back();
        pop<TileState>(val.tiles.back());
    }
    assert(get_size() == 0);
}

}
