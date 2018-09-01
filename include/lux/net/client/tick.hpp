#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/alias/vec_2.hpp>
#include <lux/net/register_net_functions.hpp>
#include <lux/common/map.hpp>

namespace net::client
{

struct Tick
{
    Vector<ChkPos> chunk_requests;
    Vec2F character_dir;
    bool  is_moving;
    bool  is_jumping;
    F32   pitch;
    F32   yaw;
};

}

namespace net { REGISTER_NET_FUNCTIONS(client::Tick); }
