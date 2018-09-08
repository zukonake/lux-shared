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
    return get_size(v.conf) +
           get_size(v.client_name);
}

void clear_buffer(Init &v)
{
    clear_buffer(v.conf);
    clear_buffer(v.client_name);
}

Serializer &operator<<(Serializer &in, Init const &v)
{
    in << v.conf;
    in << v.client_name;
    return in;
}

Deserializer &operator>>(Deserializer &out, Init &v)
{
    out >> v.conf;
    out >> v.client_name;
    return out;
}

}
