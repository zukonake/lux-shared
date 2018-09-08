#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/server/geometry_update.hpp>
#include <lux/net/vector.inl>

namespace net
{

using namespace server;

SizeT get_size(GeometryUpdate const &v)
{
    return get_size(v.pos) + get_size(v.updates);
}

void clear_buffer(GeometryUpdate &v)
{
    clear_buffer(v.pos);
    clear_buffer(v.updates);
}

Serializer &operator<<(Serializer &in, GeometryUpdate const &v)
{
    in << v.pos;
    in << v.updates;
    return in;
}

Deserializer &operator>>(Deserializer &out, GeometryUpdate &v)
{
    out >> v.pos;
    out >> v.updates;
    return out;
}

}
