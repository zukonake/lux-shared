#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/common/chunk.hpp>
#include <lux/serial/tile_data.hpp>

namespace serial
{

class Serializer;
class Deserializer;

#pragma pack(push, 1)
struct ChunkData
{
    chunk::Pos pos;
    Array<TileData, chunk::TILE_SIZE> tiles;
};
#pragma pack(pop)

SizeT get_size(ChunkData const &v);
Serializer &operator<<(Serializer &in, ChunkData const &v);
Deserializer &operator>>(Deserializer &out, ChunkData &v);

}