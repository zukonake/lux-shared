#include <cassert>
#include <stdexcept>
//
#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <net/net_order.hpp>
#include <net/tile_state.hpp>
#include "server_data.hpp"

namespace net
{

void ServerData::serialize(ServerData const &server_data, Vector<U8> &bytes)
{
    static_assert(sizeof(TileState::shape) == 1);
    static_assert(sizeof(TileState::tex_pos) == 2);
    assert(bytes.size() == 0);

    const SizeT single_size = sizeof(TileState);

    bytes.reserve(server_data.tiles.size() * single_size);
    for(auto const &i : server_data.tiles)
    {
        bytes.emplace_back(i.shape);
        bytes.emplace_back(i.tex_pos.x);
        bytes.emplace_back(i.tex_pos.y);
    }
}


void ServerData::deserialize(ServerData &server_data, Vector<U8> const &bytes)
{
    const SizeT single_size = sizeof(TileState);
    if((bytes.size() % single_size) != 0)
    {
        throw std::runtime_error("invalid server data deserialization input");
    }
    const SizeT tile_num = bytes.size() / single_size;

    server_data.tiles.reserve(tile_num);
    for(SizeT i = 0; i < tile_num; ++i)
    {
        server_data.tiles.emplace_back(
            (TileState::Shape)bytes[(i * single_size) + 0],
            TileState::TexPos(bytes[(i * single_size) + 1], bytes[(i * single_size) + 2]));
    }
}

}
