#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/common/entity.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>
#include <lux/serial/vector.hpp>
#include <lux/serial/vec_3.hpp>
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

inline SizeT get_size(ServerData const &v)
{
    return get_size(v.chunks) +
           get_size(v.entities) +
           get_size(v.player_pos);
}

inline void clear_buffer(ServerData &v)
{
    clear_buffer(v.chunks);
    clear_buffer(v.entities);
    clear_buffer(v.player_pos);
}

inline Serializer &operator<<(Serializer &in, ServerData const &v)
{
    in << v.chunks;
    in << v.entities;
    in << v.player_pos;
    return in;
}

inline Deserializer &operator>>(Deserializer &out, ServerData &v)
{
    out >> v.chunks;
    out >> v.entities;
    out >> v.player_pos;
    return out;
}

}
