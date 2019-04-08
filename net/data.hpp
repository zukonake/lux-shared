#pragma once

#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/serial.hpp>
#include <lux_shared/map.hpp>
#include <lux_shared/entity.hpp>

#pragma pack(push, 1)

struct NetSsInit {
    Arr<char, SERVER_NAME_LEN> name;
    U16                   tick_rate;
};

struct NetSsTick {
    struct EntityComps {
        typedef EntityVec    Pos;
        typedef DynArr<char> Name;
        struct Model {
            U32 id;
        };
        struct Orientation {
            Vec3F origin;
            Vec2F angles;
        };

        IdMap<EntityId, Pos>         pos;
        IdMap<EntityId, Name>        name;
        IdMap<EntityId, Model>       model;
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
            DynArr<BlockFace> faces;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    struct ChunkUpdate {
        struct Chunk {
            DynArr<Uns>       removed_faces;
            DynArr<BlockFace> added_faces;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    enum Tag : U8 {
        CHUNK_LOAD = 0x00,
        CHUNK_UPDATE,
        TAG_MAX,
    } tag = TAG_MAX;

    ChunkLoad     chunk_load;
    ChunkUpdate   chunk_update;
};

struct NetCsTick {
    EntityVec move_dir;
    bool      is_moving;
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
    enum Tag : U8 {
        MAP_REQUEST = 0x00,
        CHUNK_UNLOAD,
        TAG_MAX,
    } tag = TAG_MAX;

    MapRequest  map_request;
    ChunkUnload chunk_unload;
};

#pragma pack(pop)
