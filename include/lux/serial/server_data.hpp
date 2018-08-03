#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/common/entity.hpp>
#include <lux/serial/chunk_data.hpp>

namespace serial
{

#pragma pack(push, 1)
struct ServerData
{
    Vector<ChunkData>   chunks;
    Vector<entity::Pos> entities;
    entity::Pos         player_pos;
};
#pragma pack(pop)

class Serializer;
class Deserializer;

SizeT get_size(ServerData const &v);
void clear_buffer(ServerData &v);
Serializer &operator<<(Serializer &in, ServerData const &v);
Deserializer &operator>>(Deserializer &out, ServerData &v);

}
