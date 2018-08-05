#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>

namespace net::server::signal
{

struct Conf
{
    F64          tick_rate;
    Vector<char> server_name;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::signal::Conf); }
