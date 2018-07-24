#include <lux/serial/get_size.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/tile_data.hpp>

namespace serial
{

SizeT get_size(TileData const &v)
{
    return get_size(v.db_hash);
}

Serializer &operator<<(Serializer &in, TileData const &v)
{
    in << v.db_hash;
    return in;
}

Deserializer &operator>>(Deserializer &out, TileData &v)
{
    out >> v.db_hash;
    return out;
}

}
