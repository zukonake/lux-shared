#pragma once

#include <lux_shared/common.hpp>
#include <lux_shared/net/common.hpp>
#include <lux_shared/net/serial.hpp>
#include <lux_shared/map.hpp>
#include <lux_shared/entity.hpp>

struct NetSsInit {
    Arr<char, SERVER_NAME_LEN> name;
    U16                   tick_rate;
};

struct NetSsTick {
    struct EntityComps {
        typedef EntityVec Pos;
        typedef DynArr<char>   Name;
        struct Visible {
            U32   visible_id;
            Vec2F quad_sz;
        };
        struct Item {
            F32 weight;
        };
        struct Destructible {
            F32 dur;
            F32 dur_max;
        };
        struct Health {
            F32 hp;
            F32 hp_max;
        };
        struct Container {
            DynArr<EntityId> items;
        };
        struct Orientation {
            Vec2F origin;
            F32   angle; ///in radians
        };

        IdMap<EntityId, Pos>         pos;
        IdMap<EntityId, Name>        name;
        IdMap<EntityId, Visible>     visible;
        IdMap<EntityId, Item>        item;
        IdMap<EntityId, Container>   container;
        IdMap<EntityId, Orientation> orientation;
        IdMap<EntityId, EntityId>    parent;
    };
    struct DbgInf {
        struct Shape {
            struct Point {
                Vec2F pos;
            };
            struct Line {
                Vec2F beg;
                Vec2F end;
            };
            struct Arrow {
                Vec2F beg;
                Vec2F end;
            };
            struct Cross {
                Vec2F pos;
                F32   sz;
            };
            struct Sphere {
                Vec2F pos;
                F32   rad;
            };
            struct Triangle {
                Vec2F verts[3];
            };
            struct Rect {
                Vec2F pos;
                Vec2F sz;
                F32 angle;
            };
            enum Tag : U8 {
                POINT,
                LINE,
                ARROW,
                CROSS,
                SPHERE,
                TRIANGLE,
                RECT,
                TAG_MAX,
            } tag = TAG_MAX;
            union {
                Point point;
                Line line;
                Arrow arrow;
                Cross cross;
                Sphere sphere;
                Triangle triangle;
                Rect rect;
            };
            Vec4F col;
            bool border;
        };
        DynArr<Shape> shapes;
    };
    ///1 is expressed as midday, -1 is expressed as midnight
    F32              day_cycle;
    EntityId         player_id;
    EntityComps      entity_comps;
    DbgInf           dbg_inf;
    DynArr<EntityId> entities;
};

struct NetSsSgnl {
    struct Tiles {
        struct Chunk {
            Arr<TileId , CHK_VOL> floor;
            Arr<TileId , CHK_VOL> wall;
            Arr<TileId , CHK_VOL> roof;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    struct Light {
        struct Chunk {
            Arr<LightLvl, CHK_VOL> light_lvl;
        };
        VecMap<ChkPos, Chunk> chunks;
    };
    struct Msg {
        DynArr<char> contents;
    };
    struct RasenLabel {
        StrBuff str_id;
        U16     id;
    };
    enum Tag : U8 {
        TILES = 0x00,
        LIGHT,
        MSG,
        RASEN_LABELS,
        TAG_MAX,
    } tag = TAG_MAX;

    Tiles              tiles;
    Light              light;
    Msg                msg;
    DynArr<RasenLabel> rasen_labels;
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
    struct Command {
        DynArr<char> contents;
    };
    struct RasenAsm {
        DynArr<char> str_id;
        DynArr<char> contents;
    };
    enum Tag : U8 {
        MAP_REQUEST = 0x00,
        COMMAND,
        RASEN_ASM,
        TAG_MAX,
    } tag = TAG_MAX;

    MapRequest map_request;
    Command    command;
    RasenAsm   rasen_asm;

    DynArr<NetAction> actions;
};
