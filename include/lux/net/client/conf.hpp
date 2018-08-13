#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/net/register_net_functions.hpp>

namespace net::client
{

struct Conf
{
    F32 load_range;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Conf); }
