#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/vector.inl>
#include <lux/net/vec_2.inl>
#include <lux/net/vec_3.inl>
#include <lux/net/client/tick.hpp>

namespace net
{

using namespace client;

SizeT get_size(Tick const &v)
{
    return get_size(v.chunk_requests) +
           get_size(v.character_dir) +
           get_size(v.is_moving) +
           get_size(v.is_jumping) +
           get_size(v.pitch) +
           get_size(v.yaw);
}

void clear_buffer(Tick &v)
{
    clear_buffer(v.chunk_requests);
    clear_buffer(v.character_dir);
    clear_buffer(v.is_moving);
    clear_buffer(v.is_jumping);
    clear_buffer(v.pitch);
    clear_buffer(v.yaw);
}

Serializer &operator<<(Serializer &in, Tick const &v)
{
    in << v.chunk_requests;
    in << v.character_dir;
    in << v.is_moving;
    in << v.is_jumping;
    in << v.pitch;
    in << v.yaw;
    return in;
}

Deserializer &operator>>(Deserializer &out, Tick &v)
{
    out >> v.chunk_requests;
    out >> v.character_dir;
    out >> v.is_moving;
    out >> v.is_jumping;
    out >> v.pitch;
    out >> v.yaw;
    return out;
}

}
