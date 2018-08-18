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
    U8       id_len = 0;
    tile::Id id_buf = v.tile_ids[0];
    for(U32 i = 1; i < CHK_VOLUME; ++i)
    {
        if(v.tile_ids[i] == id_buf && id_len < 0xFF)
        {
            id_len++;
        }
        else
        {
            in << id_len;
            in << id_buf;
            id_len = 0;
            id_buf = v.tile_ids[i];
        }
    }
    in << id_len;
    in << id_buf;
    return in;
}

Deserializer &operator>>(Deserializer &out, Chunk &v)
{
    out >> v.pos;
    U32 i = 0;
    U8  id_num;
    tile::Id id_buf;
    while(i < CHK_VOLUME)
    {
        out >> id_num;
        out >> id_buf;
        for(U32 j = i; j < i + id_num + 1; ++j)
        {
            v.tile_ids[j] = id_buf;
        }
        i += id_num + 1;
    }
    return out;
}

}
