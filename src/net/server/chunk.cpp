#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/array.inl>
#include <lux/net/vec_3.inl>
#include <lux/net/server/chunk.hpp>

namespace net
{

using namespace server;

SizeT get_size(Chunk const &v)
{
    return get_size(v.pos) + get_size(v.tile_ids);
}

void clear_buffer(Chunk &v)
{
    clear_buffer(v.pos);
    clear_buffer(v.tile_ids);
}

Serializer &operator<<(Serializer &in, Chunk const &v)
{
    in << v.pos;
    in << v.tile_ids;
    return in;
}

Deserializer &operator>>(Deserializer &out, Chunk &v)
{
    out >> v.pos;
    out >> v.tile_ids;
    return out;
}

}
