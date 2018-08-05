#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/common/entity.hpp>

namespace net::server
{

struct Tick
{
    Vector<entity::Pos> entities;
    entity::Pos         player_pos;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Tick); }
