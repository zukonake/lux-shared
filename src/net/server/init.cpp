#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/vector.inl>
#include <lux/net/vec_3.inl>
#include <lux/net/server/init.hpp>

namespace net
{

using namespace server;

SizeT get_size(Init const &v)
{
    return get_size(v.tick_rate) +
           get_size(v.server_name) +
           get_size(v.chunk_size);
}

void clear_buffer(Init &v)
{
    clear_buffer(v.tick_rate);
    clear_buffer(v.server_name);
    clear_buffer(v.chunk_size);
}

Serializer &operator<<(Serializer &in, Init const &v)
{
    in << v.tick_rate;
    in << v.server_name;
    in << v.chunk_size;
    return in;
}

Deserializer &operator>>(Deserializer &out, Init &v)
{
    out >> v.tick_rate;
    out >> v.server_name;
    out >> v.chunk_size;
    return out;
}

}
