#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/common/chunk.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/clear_buffer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/vec_3.hpp>
#include <lux/serial/array.hpp>
#include <lux/serial/tile_data.hpp>

namespace serial
{

#pragma pack(push, 1)
struct ChunkData
{
    chunk::Pos pos;
    Array<TileData, chunk::TILE_SIZE> tiles;
};
#pragma pack(pop)

inline SizeT get_size(ChunkData const &v)
{
    return get_size(v.pos) + get_size(v.tiles);
}

inline void clear_buffer(ChunkData &v)
{
    clear_buffer(v.pos);
    clear_buffer(v.tiles);
}

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
