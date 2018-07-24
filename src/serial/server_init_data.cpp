#include <lux/serial/get_size.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/vector.hpp>
#include <lux/serial/server_init_data.hpp>

namespace serial
{

SizeT get_size(ServerInitData const &v)
{
    return get_size(v.tick_rate) + get_size(v.server_name);
}

Serializer &operator<<(Serializer &in, ServerInitData const &v)
{
    in << v.tick_rate;
    in << v.server_name;
    return in;
}

Deserializer &operator>>(Deserializer &out, ServerInitData &v)
{
    out >> v.tick_rate;
    out >> v.server_name;
    return out;
}

}
