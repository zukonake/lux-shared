#pragma once

#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <net/tile_state.hpp>
#include <net/serialize.hpp>
#include <net/deserialize.hpp>

namespace net
{

#pragma pack(push, 1)
struct ServerData
{
    Vector<TileState> tiles;
};
#pragma pack(pop)

template<>
inline void serialize<ServerData>(Vector<U8> &bytes, ServerData const &val)
{
    assert(bytes.size() == 0);
    bytes.reserve(val.tiles.size() * sizeof(TileState));
    for(auto const &i : val.tiles)
    {
        serialize<TileState>(bytes, i);
    }
}

template<>
inline void deserialize<ServerData>(Vector<U8> &bytes, ServerData &val)
{
    assert((bytes.size() % sizeof(TileState)) == 0);

    const SizeT tile_num = bytes.size() / sizeof(TileState);

    val.tiles.reserve(tile_num);
    for(SizeT i = 0; i < tile_num; ++i)
    {
        val.tiles.emplace_back();
        deserialize<TileState>(bytes, val.tiles.back());
    }
}

}
