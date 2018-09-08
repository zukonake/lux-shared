#pragma once

#include <lux/alias/array.hpp>
#include <lux/world/map.hpp>

namespace net::server
{

struct LightningUpdate
{
    ChkPos pos;
    Array<LightLvl, CHK_VOLUME> light_lvls;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::LightningUpdate); }

