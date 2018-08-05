#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/net/register_net_functions.hpp>

namespace net::client
{

struct Signal
{
    enum : U8
    {
        PLACEHOLDER
    } type;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Signal); }
