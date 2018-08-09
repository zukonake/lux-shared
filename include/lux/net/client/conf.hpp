#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vec_3.hpp>
#include <lux/net/register_net_functions.hpp>

namespace net::client
{

struct Conf
{
    Vec3<U8>    view_range;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Conf); }
