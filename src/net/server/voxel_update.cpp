#include <lux/net/serializer.hpp>
#include <lux/net/deserializer.hpp>
#include <lux/net/get_size.hpp>
#include <lux/net/clear_buffer.hpp>
#include <lux/net/server/voxel_update.hpp>

namespace net
{

using namespace server;

SizeT get_size(VoxelUpdate const &v)
{
    return get_size(v.idx) + get_size(v.id);
}

void clear_buffer(VoxelUpdate &v)
{
    clear_buffer(v.idx);
    clear_buffer(v.id);
}

Serializer &operator<<(Serializer &in, VoxelUpdate const &v)
{
    in << v.idx;
    in << v.id;
    return in;
}

Deserializer &operator>>(Deserializer &out, VoxelUpdate &v)
{
    out >> v.idx;
    out >> v.id;
    return out;
}

}
