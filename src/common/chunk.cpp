#include <lux/common/chunk.hpp>

namespace chunk
{

Pos to_pos(map::Pos const &pos)
{
    Pos result = pos;
    if(result.x < 0)
    {
        result.x -= SIZE.x - 1;
    }
    if(result.y < 0)
    {
        result.y -= SIZE.y - 1;
    }
    if(result.z < 0)
    {
        result.z -= SIZE.z - 1;
    }
    result.x /= SIZE.x;
    result.y /= SIZE.y;
    result.z /= SIZE.z;
    return result;
}

Index to_index(map::Pos const &pos)
{
    map::Pos result = pos;
    result.x %= SIZE.x;
    result.y %= SIZE.y;
    result.z %= SIZE.z;
    if(result.x < 0)
    {
        result.x += SIZE.x;
    }
    if(result.y < 0)
    {
        result.y += SIZE.y;
    }
    if(result.z < 0)
    {
        result.z += SIZE.z;
    }
    return (Index)(result.x + (result.y * SIZE.x) + (result.z * SIZE.x * SIZE.y));
}

map::Pos to_map_pos(Pos const &pos, Index const &idx)
{
    return (map::Pos)(pos * (Pos)SIZE) +
        map::Pos(idx % SIZE.x, (idx / SIZE.x) % SIZE.y, idx / (SIZE.x * SIZE.y));
}

}
