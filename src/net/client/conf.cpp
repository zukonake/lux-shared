#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/vec_3.inl>
#include <lux/net/client/conf.hpp>

namespace net
{

using namespace client;

SizeT get_size(Conf const &v)
{
    return get_size(v.view_range);
}

void clear_buffer(Conf &v)
{
    clear_buffer(v.view_range);
}

Serializer &operator<<(Serializer &in, Conf const &v)
{
    in << v.view_range;
    return in;
}

Deserializer &operator>>(Deserializer &out, Conf &v)
{
    out >> v.view_range;
    return out;
}

}
