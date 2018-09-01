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
    return get_size(v.pos) + get_size(v.voxels);
}

void clear_buffer(Chunk &v)
{
    clear_buffer(v.pos);
    clear_buffer(v.voxels);
}

Serializer &operator<<(Serializer &in, Chunk const &v)
{
    //TODO generalized function
    in << v.pos;
    U8       id_len = 0;
    VoxelId id_buf = v.voxels[0];
    for(U32 i = 1; i < CHK_VOLUME; ++i)
    {
        if(v.voxels[i] == id_buf && id_len < 0xFF)
        {
            id_len++;
        }
        else
        {
            in << id_len;
            in << id_buf;
            id_len = 0;
            id_buf = v.voxels[i];
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
    VoxelId id_buf;
    while(i < CHK_VOLUME)
    {
        out >> id_num;
        out >> id_buf;
        for(U32 j = i; j < i + id_num + 1; ++j)
        {
            v.voxels[j] = id_buf;
        }
        i += id_num + 1;
    }
    return out;
}

}
