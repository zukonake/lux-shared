#pragma once

#include <lux_shared/common.hpp>
#include <lux_shared/map.hpp>
#include <lux_shared/entity.hpp>

#pragma pack(push, 1)

#define LUX_ASSERT_POD(ident) \
    static_assert(std::is_trivial<ident>::value); \
    static_assert(std::is_standard_layout<ident>::value);

///actual dynamic data should be allocated after the struct data, in the same
///order as it is defined in the type
template<typename T>
struct NetDynArr {
    U32 len;
};
LUX_ASSERT_POD(NetDynArr<void>);

struct NetServerInit {
    Arr<U8, SERVER_NAME_LEN> name;
    U16 tick_rate;
};
LUX_ASSERT_POD(NetServerInit);

struct NetServerTick {
    EntityVec player_pos;
};
LUX_ASSERT_POD(NetServerTick);

struct NetServerSignal {
    struct MapLoad {
        struct Chunk {
            ChkPos pos;
            Arr<VoxelId , CHK_VOL> voxels;
            Arr<LightLvl, CHK_VOL> light_lvls;
        };
        NetDynArr<Chunk> chunks;
    };
    enum Type : U8 {
        MAP_LOAD = 0x00,
    } type;
    union {
        MapLoad map_load;
    };
};
LUX_ASSERT_POD(NetServerSignal);

struct NetClientInit {
    struct {
        U8 major;
        U8 minor;
        U8 patch;
        static_assert(sizeof(major) == sizeof(NET_VERSION_MAJOR));
        static_assert(sizeof(minor) == sizeof(NET_VERSION_MINOR));
        static_assert(sizeof(patch) == sizeof(NET_VERSION_PATCH));
    } net_ver;
    Arr<U8, CLIENT_NAME_LEN> name;
};
LUX_ASSERT_POD(NetClientInit);

struct NetClientSignal {
    struct MapRequest {
        NetDynArr<ChkPos> requests;
    };
    enum Type : U8 {
        MAP_REQUEST = 0x00,
    } type;
    union {
        MapRequest map_request;
    };
};
LUX_ASSERT_POD(NetClientSignal);

#pragma pack(pop)
