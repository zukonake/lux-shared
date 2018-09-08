#pragma once

#include <lux/alias/vector.hpp>
#include <lux/world/map.hpp>
#include <lux/net/server/voxel_update.hpp>

namespace net::server
{

struct GeometryUpdate
{
    ChkPos pos;
    Vector<VoxelUpdate> updates;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::GeometryUpdate); }

