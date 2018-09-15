#pragma once

#include <lux_shared/int.hpp>

enum LuxRval : Uns {
    LUX_RVAL_OK = 0,
    LUX_RVAL_CMD_IN,
    LUX_RVAL_ALLOC,
    LUX_RVAL_ENET_PACKET,
    LUX_RVAL_ENET_HOST_INIT,
    LUX_RVAL_ENET_INIT,
    LUX_RVAL_ENET_SEND,
    LUX_RVAL_CLIENT_INIT,
    LUX_RVAL_CLIENT_SIGNAL,
};
