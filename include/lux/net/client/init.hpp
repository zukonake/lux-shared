#pragma once

#include <lux/alias/vector.hpp>
#include <lux/net/client/conf.hpp>
#include <lux/net/register_net_functions.hpp>

namespace net::client
{

struct Init
{
    Conf         conf;
    Vector<char> client_name;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Init); }
