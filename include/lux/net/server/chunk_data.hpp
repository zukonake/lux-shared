#pragma once

#include <lux/alias/array.hpp>
#include <lux/common/chunk.hpp>
#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/server/tile_data.hpp>

namespace net
{

#pragma pack(push, 1)
struct ChunkData
{
    chunk::Pos pos;
    Array<TileData, chunk::TILE_SIZE> tiles;
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
