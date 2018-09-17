#pragma once

#include <enet/enet.h>
#include <lux_shared/common.hpp>

LUX_MAY_FAIL send_packet(ENetPeer* peer, ENetPacket* pack, U8 channel);
LUX_MAY_FAIL create_reliable_pack(ENetPacket*& pack, SizeT sz);
LUX_MAY_FAIL create_unreliable_pack(ENetPacket*& pack, SizeT sz);
