#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/util/log.hpp>

namespace net::server::signal
{

struct Msg
{
    util::LogLevel log_level;
    Vector<char>   log_msg;
};

}

#include <lux/net/register_net_functions.hpp>

namespace net { REGISTER_NET_FUNCTIONS(server::signal::Msg); }
