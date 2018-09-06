#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/world/entity.hpp>

namespace net::server
{

struct Tick
{
    Vector<EntityPos> entities;
    EntityPos         player_pos;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Tick); }
