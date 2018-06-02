#include <vector>
#include <cstdint>
//
#include <net/net_order.hpp>
#include <world/tile/type.hpp>
#include "client_data.hpp"

namespace net
{

std::vector<uint8_t> ClientData::serialize() //TODO take reference instead of return?
{
    static_assert(sizeof(view_size) == 4);

    std::vector<uint8_t> result(sizeof(view_size));
    result[0] =  net_order<uint16_t>(view_size.x) & 0xFF;
    result[1] = (net_order<uint16_t>(view_size.x) & 0xFF00) >> 8;
    result[2] =  net_order<uint16_t>(view_size.y) & 0xFF;
    result[3] = (net_order<uint16_t>(view_size.y) & 0xFF00) >> 8;
    return result;
}


ClientData ClientData::deserialize(std::vector<uint8_t> const &bytes)
{
    static_assert(sizeof(view_size) == 4);

    const std::size_t single_size = sizeof(view_size);
    if(bytes.size() != single_size)
    {
        throw std::runtime_error("invalid client data deserialization input");
    }
    const std::size_t tile_num    = bytes.size() / single_size;
    ClientData result = {{0, 0}};
    result.view_size.x = net_order<uint16_t>(bytes[0] | (bytes[1] << 8));
    result.view_size.y = net_order<uint16_t>(bytes[2] | (bytes[3] << 8));
    return result;
}

}

