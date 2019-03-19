#pragma once

#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/serial.hpp>
#include <lux_shared/map.hpp>
#include <lux_shared/entity.hpp>

#pragma pack(push, 1)

struct NetRasenLabel {
    StrBuff str_id;
    U16     id;
};

struct NetSsInit {
    Arr<char, SERVER_NAME_LEN> name;
    U16                   tick_rate;
    DynArr<NetRasenLabel> rasen_labels;
};

struct NetSsTick {
    struct EntityComps {
        typedef EntityVec Pos;
        typedef DynArr<char>   Name;
        struct Visible {
            U32   visible_id;
        };
        struct Orientation {
            Vec3F origin;
            Vec2F angles;
        };

        IdMap<EntityId, Pos>         pos;
        IdMap<EntityId, Name>        name;
        IdMap<EntityId, Visible>     visible;
        IdMap<EntityId, Orientation> orientation;
        IdMap<EntityId, EntityId>    parent;
    };
    ///1 is expressed as midday, -1 is expressed as midnight
    F32              day_cycle;
    EntityId         player_id;
    EntityComps      entity_comps;
    DynArr<EntityId> entities;
};

struct NetSsSgnl {
    struct ChunkLoad {
        struct Chunk {
            struct Vert {
                Vec3<U16> pos;  ///12.4 fixed point
                Vec3<U8>  norm; ///sign.7 fixed point
                BlockId  id;
            };
            DynArr<Vert> verts;
            DynArr<U16> idxs;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    /*struct ChunkUpdate {
        struct Chunk {
            IdMap<ChkIdx, Block> blocks;
        };
        VecMap<ChkPos, Chunk> chunks;
    };*/
    struct Msg {
        DynArr<char> contents;
    };
    enum Tag : U8 {
        CHUNK_LOAD = 0x00,
        //CHUNK_UPDATE,
        MSG,
        RASEN_LABEL,
        TAG_MAX,
    } tag = TAG_MAX;

    ChunkLoad     chunk_load;
    //ChunkUpdate   chunk_update;
    Msg           msg;
    NetRasenLabel rasen_label;
};

struct NetAction {
    DynArr<U8> stack;
    U16           id;
};

struct NetCsTick {
    DynArr<NetAction> actions;
};

struct NetCsInit {
    struct {
        U8 major;
        U8 minor;
        U8 patch;
        static_assert(sizeof(major) == sizeof(NET_VERSION_MAJOR));
        static_assert(sizeof(minor) == sizeof(NET_VERSION_MINOR));
        static_assert(sizeof(patch) == sizeof(NET_VERSION_PATCH));
    } net_ver;
    Arr<char, CLIENT_NAME_LEN> name;
};

struct NetCsSgnl {
    struct MapRequest {
        VecSet<ChkPos> requests;
    };
    struct ChunkUnload {
        VecSet<ChkPos> chunks;
    };
    struct RasenAsm {
        DynArr<char> str_id;
        DynArr<char> contents;
    };
    enum Tag : U8 {
        MAP_REQUEST = 0x00,
        CHUNK_UNLOAD,
        RASEN_ASM,
        TAG_MAX,
    } tag = TAG_MAX;

    MapRequest  map_request;
    ChunkUnload chunk_unload;
    RasenAsm    rasen_asm;

    DynArr<NetAction> actions;
};

#pragma pack(pop)
