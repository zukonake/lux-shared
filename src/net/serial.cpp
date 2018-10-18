#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/serial.hpp>

LUX_MAY_FAIL buff_sz_at_least(SizeT sz, U8 const* iter, U8 const* end) {
    LUX_ASSERT(end >= iter);
    SizeT actual = end - iter;
    if(actual < sz) {
        LUX_LOG_ERR("invalid packet, expected atleast %zu, got %zu", sz, actual);
        return LUX_FAIL;
    }
    return LUX_OK;
}
