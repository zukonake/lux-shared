#pragma once

#include <lux/alias/vector.hpp>
#include <lux/net/server/chunk.hpp>

namespace net::server::signal
{

struct Map
{
    Vector<Chunk>   chunks;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::signal::Map); }
