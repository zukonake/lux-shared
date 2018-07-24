#include <lux/serial/get_size.hpp>
#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/vec_3.hpp>
#include <lux/serial/array.hpp>
#include <lux/serial/tile_data.hpp>
#include <lux/serial/chunk_data.hpp>

namespace serial
{

SizeT get_size(ChunkData const &v)
{
    return get_size(v.pos) + get_size(v.tiles);
}

Serializer &operator<<(Serializer &in, ChunkData const &v)
{
    in << v.pos;
    in << v.tiles;
    return in;
}

Deserializer &operator>>(Deserializer &out, ChunkData &v)
{
    out >> v.pos;
    out >> v.tiles;
    return out;
}

}
