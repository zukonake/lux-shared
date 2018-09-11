#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/client/init.hpp>
#include <lux/net/vector.inl>

namespace net
{

using namespace client;

SizeT get_size(Init const &v)
{
    return get_size(v.load_range) +
           get_size(v.client_name);
}

void clear_buffer(Init &v)
{
    clear_buffer(v.load_range);
    clear_buffer(v.client_name);
}

Serializer &operator<<(Serializer &in, Init const &v)
{
    in << v.load_range;
    in << v.client_name;
    return in;
}

Deserializer &operator>>(Deserializer &out, Init &v)
{
    out >> v.load_range;
    out >> v.client_name;
    return out;
}

}
