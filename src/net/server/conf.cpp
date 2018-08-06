#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/vector.inl>
#include <lux/net/server/conf.hpp>

namespace net
{

using namespace server;

SizeT get_size(Conf const &v)
{
    return get_size(v.tick_rate) + get_size(v.server_name);
}

void clear_buffer(Conf &v)
{
    clear_buffer(v.tick_rate);
    clear_buffer(v.server_name);
}

Serializer &operator<<(Serializer &in, Conf const &v)
{
    in << v.tick_rate;
    in << v.server_name;
    return in;
}

Deserializer &operator>>(Deserializer &out, Conf &v)
{
    out >> v.tick_rate;
    out >> v.server_name;
    return out;
}

}
