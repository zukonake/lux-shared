#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/enet.hpp>

LUX_MAY_FAIL send_packet(ENetPeer* peer, ENetHost *host,
                         Slice<U8> slice, U8 channel, U32 flags) {
    auto log_fail= [&]() {
        U8* ip = get_ip(peer->address);
        LUX_LOG("    data size: %zuB", slice.len);
        LUX_LOG("    channel: %u", channel);
        LUX_LOG("    flags: %x", flags);
        LUX_LOG("    peer ip: %u.%u.%u.%u", ip[0], ip[1], ip[2], ip[4]);
        LUX_LOG("    peer data: %zu", (SizeT)peer->data);
    };
    ENetPacket* pack = enet_packet_create(slice.beg, slice.len,
        ENET_PACKET_FLAG_NO_ALLOCATE | flags);
    if(pack == nullptr) {
        LUX_LOG("failed to create enet packet"); //@TODO more info
        log_fail();
        return LUX_FAIL;
    }
    if(enet_peer_send(peer, channel, pack) < 0) {
        LUX_LOG("failed to send enet packet"); //@TODO more info
        log_fail();
        return LUX_FAIL;
    }
    enet_host_flush(host);
    return LUX_OK;
}

LUX_MAY_FAIL send_init(ENetPeer* peer, ENetHost *host, Slice<U8> slice) {
    return send_packet(peer, host, slice,
                       INIT_CHANNEL, ENET_PACKET_FLAG_RELIABLE);
}

LUX_MAY_FAIL send_tick(ENetPeer* peer, ENetHost *host, Slice<U8> slice) {
    return send_packet(peer, host, slice,
                       TICK_CHANNEL, ENET_PACKET_FLAG_UNSEQUENCED);
}

LUX_MAY_FAIL send_signal(ENetPeer* peer, ENetHost *host, Slice<U8> slice) {
    return send_packet(peer, host, slice,
                       SIGNAL_CHANNEL, ENET_PACKET_FLAG_RELIABLE);
}
