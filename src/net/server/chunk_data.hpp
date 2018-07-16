#pragma once

#include <consts.hpp>
#include <common/chunk.hpp>
#include <net/server/tile_data.hpp>

namespace net
{

#pragma pack(push, 1)
struct ChunkData
{
    ChunkPos pos;
    TileData tiles[consts::CHUNK_TILE_SIZE];
};
#pragma pack(pop)

inline Serializer &operator<<(Serializer &in, ChunkData const &v)
{
    in << v.pos;
    in << v.tiles;
    return in;
}

inline Deserializer &operator>>(Deserializer &out, ChunkData &v)
{
    out >> v.pos;
    out >> v.tiles;
    return out;
}

}
