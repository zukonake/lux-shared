#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/server/tick.hpp>
#include <lux/net/vector.inl>
#include <lux/net/vec_3.inl>

namespace net
{

using namespace server;

SizeT get_size(Tick const &v)
{
    return get_size(v.entities) +
           get_size(v.player_pos);
}

void clear_buffer(Tick &v)
{
    clear_buffer(v.entities);
    clear_buffer(v.player_pos);
}

Serializer &operator<<(Serializer &in, Tick const &v)
{
    in << v.entities;
    in << v.player_pos;
    return in;
}

Deserializer &operator>>(Deserializer &out, Tick &v)
{
    out >> v.entities;
    out >> v.player_pos;
    return out;
}

}
