#pragma once

#include <enet/enet.h>
#include <lux_shared/common.hpp>

LUX_MAY_FAIL send_packet(ENetPeer* peer, Slice<U8> slice, U8 channel, U32 flags);
LUX_MAY_FAIL send_init(ENetPeer* peer, Slice<U8> slice);
LUX_MAY_FAIL send_tick(ENetPeer* peer, Slice<U8> slice);
LUX_MAY_FAIL send_signal(ENetPeer* peer, Slice<U8> slice);
