#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/serial/chunk_data.hpp>
#include <lux/common/entity.hpp>

namespace serial
{

class Serializer;
class Deserializer;

#pragma pack(push, 1)
struct ServerData
{
    Vector<ChunkData>   chunks;
    Vector<entity::Pos> entities;
    entity::Pos         player_pos;
};
#pragma pack(pop)

SizeT get_size(ServerData const &v);
Serializer &operator<<(Serializer &in, ServerData const &v);
Deserializer &operator>>(Deserializer &out, ServerData &v);

}
