#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/alias/vec_3.hpp>

namespace net::server
{

struct Init
{
    F64          tick_rate;
    Vector<char> server_name;
    Vec3<U16>    chunk_size;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::Init); }
