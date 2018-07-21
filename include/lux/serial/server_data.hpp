#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/hash.hpp>
#include <lux/alias/vector.hpp>
#include <lux/alias/array.hpp>
#include <lux/linear/vec_3.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/common/entity.hpp>
#include <lux/common/chunk.hpp>

namespace serial
{

#pragma pack(push, 1)
struct ServerInitData
{
    F64                 tick_rate;
    Vector<char>        server_name;
    linear::Vec3<SizeT> chunk_size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct TileData
{
    Hash db_hash;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ChunkData
{
    chunk::Pos pos;
    Array<TileData, chunk::TILE_SIZE> tiles;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct ServerData
{

    Vector<ChunkData>   chunks;
    Vector<entity::Pos> entities;
    entity::Pos         player_pos;
};
#pragma pack(pop)

Serializer &operator<<(Serializer &in, TileData const &v);
Serializer &operator<<(Serializer &in, ChunkData const &v);
Serializer &operator<<(Serializer &in, ServerData const &v);

Deserializer &operator>>(Deserializer &out, TileData &v);
Deserializer &operator>>(Deserializer &out, ChunkData &v);
Deserializer &operator>>(Deserializer &out, ServerData &v);

}
