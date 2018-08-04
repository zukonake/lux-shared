#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>
#include <lux/serial/client_data.hpp>
#include <lux/serial/vector.inl>
#include <lux/serial/vec_2.inl>

namespace serial
{

SizeT get_size(ClientData const &v)
{
    return get_size(v.chunk_requests) +
           get_size(v.character_dir) +
           get_size(v.is_moving) +
           get_size(v.is_jumping);
}

void clear_buffer(ClientData &v)
{
    clear_buffer(v.chunk_requests);
    clear_buffer(v.character_dir);
    clear_buffer(v.is_moving);
    clear_buffer(v.is_jumping);
}

Serializer &operator<<(Serializer &in, ClientData const &v)
{
    in << v.chunk_requests;
    in << v.character_dir;
    in << v.is_moving;
    in << v.is_jumping;
    return in;
}

Deserializer &operator>>(Deserializer &out, ClientData &v)
{
    out >> v.chunk_requests;
    out >> v.character_dir;
    out >> v.is_moving;
    out >> v.is_jumping;
    return out;
}

}
