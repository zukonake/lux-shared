#include <stdexcept>
#include <cstdint>
#include <net/net_order.hpp>
#include "server_data.hpp"

namespace net
{

std::vector<uint8_t> ServerData::serialize() //TODO take reference instead of return?
{
    static_assert(sizeof(world::tile::Type::shape) == 1);
    static_assert(sizeof(world::tile::Type::tex_pos) == 2);

    const std::size_t single_size = sizeof(world::tile::Type);
    uint64_t byte_size = single_size * tiles.size();

    std::vector<uint8_t> result(byte_size);
    for(std::size_t i = 0; i < tiles.size(); ++i)
    {
        result[(i * single_size) + 0] = tiles[i].shape;
        result[(i * single_size) + 1] = tiles[i].tex_pos.x;
        result[(i * single_size) + 2] = tiles[i].tex_pos.y;
    }
    return result;
}


ServerData ServerData::deserialize(std::vector<uint8_t> const &bytes)
{
    const std::size_t single_size = sizeof(world::tile::Type);
    if((bytes.size() % single_size) != 0)
    {
        throw std::runtime_error("invalid server data deserialization input");
    }
    const std::size_t tile_num    = bytes.size() / single_size;
    ServerData result;
    result.tiles.reserve(tile_num);
    for(std::size_t i = 0; i < tile_num; ++i)
    {
        result.tiles.emplace_back(
            (world::tile::Type::Shape) bytes[(i * single_size) + 0],
            linear::Point2d<uint8_t>(
                bytes[(i * single_size) + 1],
                bytes[(i * single_size) + 2]
            ));
    }
    return result;
}

}
