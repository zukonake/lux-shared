#include <enet/enet.h>
//
#include <lux_shared/common.hpp>
#include <lux_shared/net/net_order.hpp>

LUX_MAY_FAIL check_pack_size_atleast(SizeT expected,
                                     U8 const* iter, ENetPacket* pack) {
    SizeT actual = pack->dataLength - (iter - pack->data);
    if(actual < expected) {
        LUX_LOG("invalid packet, expected atleast %zu, got %zu",
                expected, actual);
        return LUX_FAIL;
    }
    return LUX_OK;
}

LUX_MAY_FAIL check_pack_size(SizeT expected,
                             U8 const* iter, ENetPacket* pack) {
    SizeT actual = pack->dataLength - (iter - pack->data);
    if(actual != expected) {
        LUX_LOG("invalid packet, expected %zu, got %zu",
                expected, actual);
        return LUX_FAIL;
    }
    return LUX_OK;
}

template<typename T>
void deserialize(U8 const** iter, T* val) {
    static_assert(std::is_arithmetic<T>::value);
    net_order(val, (T const*)*iter);
    *iter += sizeof(T);
}

template<typename T>
void serialize(U8** iter, T const& val) {
    static_assert(std::is_arithmetic<T>::value);
    net_order((T*)*iter, &val);
    *iter += sizeof(T);
}

template<typename T, I32 N>
void deserialize(U8 const** iter, Vec<T, N>* val) {
    for(Uns i = 0; i < N; ++i) deserialize(iter, &((*val)[i]));
}

template<typename T, I32 N>
void serialize(U8** iter, Vec<T, N> const& val) {
    for(Uns i = 0; i < N; ++i) serialize(iter, val[i]);
}

template<typename T, SizeT N>
void deserialize(U8 const** iter, Arr<T, N>* val) {
    for(Uns i = 0; i < N; ++i) deserialize(iter, (T*)&((*val)[i]));
}

template<typename T, SizeT N>
void serialize(U8** iter, Arr<T, N> const& val) {
    for(Uns i = 0; i < N; ++i) serialize(iter, val[i]);
}

template<typename T>
void deserialize(U8 const** iter, T** beg, SizeT const& len) {
    for(Uns i = 0; i < len; ++i) deserialize(iter, &((*beg)[i]));
}

template<typename T>
void serialize(U8** iter, T const* beg, SizeT const& len) {
    for(Uns i = 0; i < len; ++i) serialize(iter, beg[i]);
}
