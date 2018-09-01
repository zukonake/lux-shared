#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/alias/vec_3.hpp>
#include <lux/net/server/conf.hpp>

namespace net::server
{

struct Init
{
    Conf         conf;
    Vector<char> server_name;
    Vec3UI       chunk_size;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Init); }
