#pragma once

#include <cstdint>
#include <vector>
//
#include <world/tile/type.hpp>

namespace net
{

struct ServerData
{
    std::vector<world::tile::Type> tiles;
    //tiles view size (in w and h) are client-side

    std::vector<uint8_t> serialize();
    static ServerData deserialize(std::vector<uint8_t> const &bytes);
};

}
