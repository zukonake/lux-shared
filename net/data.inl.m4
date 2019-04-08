divert(-1)
define(`m4_quote', `ifelse(`$#', `0', `', ``$*'')')
define(`m4_dquote', ``$@'')
define(`m4_dquote_elt', `ifelse(`$#', `0', `', `$#', `1', ```$1''',
                             ```$1'',$0(shift($@))')')

define(`m4_foreach', `pushdef(`$1')m4__foreach($@)popdef(`$1')')
define(`m4__arg1', `$1')
define(`m4__foreach', `ifelse(m4_quote($2), `', `',
    `define(`$1', `m4__arg1($2)')$3`'$0(`$1', `shift($2)', `$3')')')

define(`m4_lux_net_data', `dnl
dnl
dnl
ifelse(`$2', `static', `dnl

template<> struct HasStaticSz<$1> { bool static constexpr val = true; };
inline void clear_net_data($1* val) {
    m4_foreach(`member', `shift(shift($@))', `
    clear_net_data(&val->member);')
}

LUX_MAY_FAIL inline deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    LUX_RETHROW(buff_sz_at_least(sizeof($1), *buff, buff_end));dnl
    m4_foreach(`member', `shift(shift($@))', `
    (void)deserialize(buff, buff_end, &val->member);')
    return LUX_OK;
}

inline void serialize(U8** buff, $1 const& val) {dnl
    m4_foreach(`member', `shift(shift($@))', `
    serialize(buff, val.member);')
}', `dnl
dnl
dnl
ifelse(`$2', `dynamic', `dnl

inline void clear_net_data($1* val) {
    m4_foreach(`member', `shift(shift($@))', `
    clear_net_data(&val->member);')
}

inline SizeT get_real_sz($1 const& val) {
    return m4_foreach(`member', `shift(shift($@))', `
        get_real_sz(val.member) +')
        0;
}

LUX_MAY_FAIL inline deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    m4_foreach(`member', `shift(shift($@))', `
    LUX_RETHROW(deserialize(buff, buff_end, &val->member),
                "failed to deserialize member of $1");')
    return LUX_OK;
}

inline void serialize(U8** buff, $1 const& val) {dnl
    m4_foreach(`member', `shift(shift($@))', `
    serialize(buff, val.member);')
}', `dnl
dnl
dnl
ifelse(`$2', `tagged', `dnl

inline void clear_net_data($1* val) {
    switch(val->tag) {dnl
        m4_foreach(`variant', `$3', `
        case $1::translit(variant, `a-z', `A-Z'):
            clear_net_data(&val->variant);
            break;')
        default: break;
    }
    m4_foreach(`member', `shift(shift(shift($@)))', `
    clear_net_data(&val->member);')
}

inline SizeT get_real_sz($1 const& val) {
    SizeT sz = sizeof($1::Tag);
    switch(val.tag) {dnl
        m4_foreach(`variant', `$3', `
        case $1::translit(variant, `a-z', `A-Z'):
            sz += get_real_sz(val.variant);
            break;')
        default: LUX_UNREACHABLE();
    }
    m4_foreach(`member', `shift(shift(shift($@)))', `
    sz += get_real_sz(val.member);')
    return sz;
}

LUX_MAY_FAIL inline deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    LUX_RETHROW(deserialize(buff, buff_end, (U8*)&val->tag),
                "failed to deserialize $1 tag");
    switch(val->tag) {dnl
        m4_foreach(`variant', `$3', `
        case $1::translit(variant, `a-z', `A-Z'):
            LUX_RETHROW(deserialize(buff, buff_end, &val->variant),
                        "failed to deserialize variant of $1");
            break;')
        default:
            LUX_LOG_ERR("unexpected packet tag %u for $1", val->tag);
            return LUX_FAIL;
    }
    m4_foreach(`member', `shift(shift(shift($@)))', `
    LUX_RETHROW(deserialize(buff, buff_end, &val->member),
                "failed to deserialize member of $1");')
    return LUX_OK;
}

inline void serialize(U8** buff, $1 const& val) {
    serialize(buff, (U8 const&)val.tag);
    switch(val.tag) {dnl
        m4_foreach(`variant', `$3', `
        case $1::translit(variant, `a-z', `A-Z'):
            serialize(buff, val.variant); break;')
        default: LUX_UNREACHABLE();
    }
    m4_foreach(`member', `shift(shift(shift($@)))', `
    serialize(buff, val.member);')
}dnl
',)')')dnl
')dnl
divert(0)dnl
//@TODO split into cpp files?
#pragma once
#include <lux_shared/net/serial.hpp>
#include <lux_shared/net/data.hpp>

m4_lux_net_data(BlockFace, static, idx, id, orientation)
m4_lux_net_data(NetSsInit, dynamic, name, tick_rate)
m4_lux_net_data(NetSsTick::EntityComps::Model, static, id)
m4_lux_net_data(NetSsTick::EntityComps, dynamic, pos, name, model)
m4_lux_net_data(NetSsTick, dynamic, day_cycle, player_id, entity_comps,
    entities)
m4_lux_net_data(NetSsSgnl::ChunkLoad::Chunk, dynamic, faces)
m4_lux_net_data(NetSsSgnl::ChunkLoad, dynamic, chunks)
m4_lux_net_data(NetSsSgnl::ChunkUpdate::Chunk, dynamic, removed_faces, added_faces)
m4_lux_net_data(NetSsSgnl::ChunkUpdate, dynamic, chunks)
m4_lux_net_data(NetSsSgnl, tagged, `chunk_load, chunk_update')
m4_lux_net_data(NetCsSgnl::MapRequest, dynamic, requests)
m4_lux_net_data(NetCsSgnl::ChunkUnload, dynamic, chunks)
m4_lux_net_data(NetCsSgnl, tagged, `map_request, chunk_unload')
m4_lux_net_data(NetCsInit, static,
    net_ver.major, net_ver.minor, net_ver.patch, name)
m4_lux_net_data(NetCsTick, static, move_dir, yaw_pitch, is_moving)
