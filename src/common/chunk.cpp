#include <lux/common/chunk.hpp>
#include <lux/consts.hpp>

ChunkPos to_chunk_pos(MapPos const &pos)
{
    auto const &SIZE = consts::CHUNK_SIZE;
    ChunkPos result = pos;
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

ChunkIndex to_chunk_index(MapPos const &pos)
{
    auto const &SIZE = consts::CHUNK_SIZE;
    MapPos result = pos;
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
    return (ChunkIndex)(result.x + (result.y * SIZE.x) + (result.z * SIZE.x * SIZE.y));
}

MapPos chunk_to_map_pos(ChunkPos const &pos, ChunkIndex const &idx)
{
    auto const &SIZE = consts::CHUNK_SIZE;
    return (MapPos)(pos * (ChunkPos)SIZE) +
        MapPos(idx % SIZE.x, idx / SIZE.x, idx / SIZE.x * SIZE.y);
}
