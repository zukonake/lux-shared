#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/alias/vec_2.hpp>
#include <lux/net/register_net_functions.hpp>
#include <lux/common/chunk.hpp>

namespace net::client
{

struct Tick
{
    Vector<chunk::Pos> chunk_requests;
    Vec2<F32>          character_dir;
    bool is_moving;
    bool is_jumping;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Tick); }
