#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/server/map_updates.hpp>
#include <lux/net/vector.inl>

namespace net
{

using namespace server;

SizeT get_size(MapUpdates const &v)
{
    return get_size(v.geometry_updates) + get_size(v.lightning_updates);
}

void clear_buffer(MapUpdates &v)
{
    clear_buffer(v.geometry_updates);
    clear_buffer(v.lightning_updates);
}

Serializer &operator<<(Serializer &in, MapUpdates const &v)
{
    in << v.geometry_updates;
    in << v.lightning_updates;
    return in;
}

Deserializer &operator>>(Deserializer &out, MapUpdates &v)
{
    out >> v.geometry_updates;
    out >> v.lightning_updates;
    return out;
}

}
