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
           get_size(v.is_jumping);
}

void clear_buffer(Tick &v)
{
    clear_buffer(v.chunk_requests);
    clear_buffer(v.character_dir);
    clear_buffer(v.is_moving);
    clear_buffer(v.is_jumping);
}

Serializer &operator<<(Serializer &in, Tick const &v)
{
    in << v.chunk_requests;
    in << v.character_dir;
    in << v.is_moving;
    in << v.is_jumping;
    return in;
}

Deserializer &operator>>(Deserializer &out, Tick &v)
{
    out >> v.chunk_requests;
    out >> v.character_dir;
    out >> v.is_moving;
    out >> v.is_jumping;
    return out;
}

}
