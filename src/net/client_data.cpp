#include <cassert>
#include <stdexcept>
//
#include <alias/int.hpp>
#include <alias/vector.hpp>
#include <net/net_order.hpp>
#include "client_data.hpp"

namespace net
{

void ClientData::serialize(ClientData const &client_data, Vector<U8> &bytes)
{
    static_assert(sizeof(view_size) == 4);
    assert(bytes.size() == 0);

    bytes.reserve(sizeof(view_size));
    bytes.emplace_back(net_order<U16>((client_data.view_size.x) & 0x00FF));
    bytes.emplace_back(net_order<U16>((client_data.view_size.x) & 0xFF00) >> 8);
    bytes.emplace_back(net_order<U16>((client_data.view_size.y) & 0x00FF));
    bytes.emplace_back(net_order<U16>((client_data.view_size.y) & 0xFF00) >> 8);
}

void ClientData::deserialize(ClientData &client_data, Vector<U8> const &bytes)
{
    static_assert(sizeof(view_size) == 4);

    const SizeT single_size = sizeof(view_size);
    if(bytes.size() != single_size)
    {
        throw std::runtime_error("invalid client data deserialization input");
    }
    client_data.view_size.x = net_order((U16)(bytes[0] | (bytes[1] << 8)));
    client_data.view_size.y = net_order((U16)(bytes[2] | (bytes[3] << 8)));
}

}

