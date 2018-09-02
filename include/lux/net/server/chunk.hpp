#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/array.hpp>
#include <lux/common/map.hpp>

namespace net::server
{

struct Chunk
{
    ChkPos pos;
    Array<VoxelId , CHK_VOLUME> voxels;
    Array<LightLvl, CHK_VOLUME> light_lvls;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Chunk); }

