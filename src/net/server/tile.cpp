#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/server/tile.hpp>

namespace net
{

using namespace server;

SizeT get_size(Tile const &v)
{
    return get_size(v.db_hash);
}

void clear_buffer(Tile &v)
{
    clear_buffer(v.db_hash);
}

Serializer &operator<<(Serializer &in, Tile const &v)
{
    in << v.db_hash;
    return in;
}

Deserializer &operator>>(Deserializer &out, Tile &v)
{
    out >> v.db_hash;
    return out;
}

}
