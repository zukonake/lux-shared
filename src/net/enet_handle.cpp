#include <enet/enet.h>
//
#include <lux/common.hpp>
#include <lux/net/enet_handle.hpp>

namespace net
{

ENetHandle::ENetHandle()
{
    if(enet_initialize() != 0) {
        LUX_LOG("ENET_HANDLE", FATAL, "couldn't create enet handle");
    }
}

ENetHandle::~ENetHandle()
{
    enet_deinitialize();
}

}
