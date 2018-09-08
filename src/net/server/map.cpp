#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/server/map.hpp>
#include <lux/net/vector.inl>

namespace net
{

using namespace server;

SizeT get_size(Map const &v)
{
    return get_size(v.chunks);
}

void clear_buffer(Map &v)
{
    clear_buffer(v.chunks);
}

Serializer &operator<<(Serializer &in, Map const &v)
{
    in << v.chunks;
    return in;
}

Deserializer &operator>>(Deserializer &out, Map &v)
{
    out >> v.chunks;
    return out;
}

}
