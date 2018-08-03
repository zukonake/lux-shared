#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>
#include <lux/serial/vector.inl>
#include <lux/serial/vec_3.inl>
#include <lux/serial/server_data.hpp>

namespace serial
{

SizeT get_size(ServerData const &v)
{
    return get_size(v.chunks) +
           get_size(v.entities) +
           get_size(v.player_pos);
}

void clear_buffer(ServerData &v)
{
    clear_buffer(v.chunks);
    clear_buffer(v.entities);
    clear_buffer(v.player_pos);
}

Serializer &operator<<(Serializer &in, ServerData const &v)
{
    in << v.chunks;
    in << v.entities;
    in << v.player_pos;
    return in;
}

Deserializer &operator>>(Deserializer &out, ServerData &v)
{
    out >> v.chunks;
    out >> v.entities;
    out >> v.player_pos;
    return out;
}

}
