#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/net/register_net_functions.hpp>
#include <lux/net/client/conf.hpp>

namespace net::client
{

struct Signal
{
    enum : U8
    {
        CONF = 0x00,
    } type;
    Conf conf;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Signal); }
