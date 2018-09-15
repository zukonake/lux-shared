#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/enet.hpp>

LuxRval send_packet(ENetPeer* peer, ENetHost *host,
                    Slice<U8> slice, U8 channel, U32 flags) {
    ENetPacket* pack = enet_packet_create(slice.beg, slice.len,
        ENET_PACKET_FLAG_NO_ALLOCATE | flags);
    if(pack == nullptr) {
        return LUX_RVAL_ENET_PACKET;
    }
    if(enet_peer_send(peer, channel, pack) < 0) {
        return LUX_RVAL_ENET_SEND;
        //@TODO some info here
    }
    enet_host_flush(host);
    return LUX_RVAL_OK;
}

LuxRval send_init(ENetPeer* peer, ENetHost *host, Slice<U8> slice) {
    return send_packet(peer, host, slice,
                       INIT_CHANNEL, ENET_PACKET_FLAG_RELIABLE);
}

LuxRval send_tick(ENetPeer* peer, ENetHost *host, Slice<U8> slice) {
    return send_packet(peer, host, slice,
                       TICK_CHANNEL, ENET_PACKET_FLAG_UNSEQUENCED);
}

LuxRval send_signal(ENetPeer* peer, ENetHost *host, Slice<U8> slice) {
    return send_packet(peer, host, slice,
                       SIGNAL_CHANNEL, ENET_PACKET_FLAG_RELIABLE);
}
