#pragma once

#include <lux/alias/scalar.hpp>

namespace net::server
{

struct Conf
{
    F64          tick_rate;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Conf); }
