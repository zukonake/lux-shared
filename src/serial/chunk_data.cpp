#include <lux/serial/serializer.hpp>
#include <lux/serial/deserializer.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>
#include <lux/serial/array.inl>
#include <lux/serial/vec_3.inl>
#include <lux/serial/chunk_data.hpp>

namespace serial
{

SizeT get_size(ChunkData const &v)
{
    return get_size(v.pos) + get_size(v.tiles);
}

void clear_buffer(ChunkData &v)
{
    clear_buffer(v.pos);
    clear_buffer(v.tiles);
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
