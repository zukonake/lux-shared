#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/server/lightning_update.hpp>
#include <lux/net/array.inl>

namespace net
{

using namespace server;

SizeT get_size(LightningUpdate const &v)
{
    return get_size(v.pos) + get_size(v.light_lvls);
}

void clear_buffer(LightningUpdate &v)
{
    clear_buffer(v.pos);
    clear_buffer(v.light_lvls);
}

Serializer &operator<<(Serializer &in, LightningUpdate const &v)
{
    in << v.pos;
    in << v.light_lvls;
    return in;
}

Deserializer &operator>>(Deserializer &out, LightningUpdate &v)
{
    out >> v.pos;
    out >> v.light_lvls;
    return out;
}

}
