#pragma once

#include <lux/world/map.hpp>

namespace net::server
{

struct VoxelUpdate
{
    ChkIdx idx;
    VoxelId id;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::VoxelUpdate); }

