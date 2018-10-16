divert(-1)
define(`quote', `ifelse(`$#', `0', `', ``$*'')')
define(`dquote', ``$@'')
define(`dquote_elt', `ifelse(`$#', `0', `', `$#', `1', ```$1''',
                             ```$1'',$0(shift($@))')')

define(`foreach', `pushdef(`$1')_foreach($@)popdef(`$1')')
define(`_arg1', `$1')
define(`_foreach', `ifelse(quote($2), `', `',
    `define(`$1', `_arg1($2)')$3`'$0(`$1', `shift($2)', `$3')')')

define(`m4_formember', `foreach(`member', `shift(shift($1))', `$2')')
define(`m4_lux_net_data', `dnl
dnl
dnl
ifelse(`$2', `static', `dnl

template<> struct HasStaticSz<$1> { bool static constexpr val = true; };
void clear_net_data($1* val) {
    m4_formember(`$@', `
    clear_net_data(&val->member);')
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    if(buff_sz_at_least(sizeof($1), *buff, buff_end) != LUX_OK) {
        return LUX_FAIL;
    }dnl
    m4_formember(`$@', `
    (void)deserialize(buff, buff_end, &val->member);')
    return LUX_OK;
}

void serialize(U8** buff, $1 const& val) {dnl
    m4_formember(`$@', `
    serialize(buff, val.member);')
}', `dnl
dnl
dnl
ifelse(`$2', `dynamic', `dnl

void clear_net_data($1* val) {
    m4_formember(`$@', `
    clear_net_data(&val->member);')
}

SizeT get_real_sz($1 const& val) {
    return m4_formember(`$@', `
        get_real_sz(val.member) +')
        0;
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    if(m4_formember(`$@',`
       deserialize(buff, buff_end, &val->member) != LUX_OK ||')
       false) {
       return LUX_FAIL;
    }
    return LUX_OK;
}

void serialize(U8** buff, $1 const& val) {dnl
    m4_formember(`$@', `
    serialize(buff, val.member);')
}', `dnl
dnl
dnl
ifelse(`$2', `tagged', `dnl

void clear_net_data($1* val) {
    switch(val->tag) {dnl
        m4_formember(`$@', `
        case $1::translit(member, `a-z', `A-Z'):
            m4_formember(`$@', `
            clear_net_data(&val->member);')
            break;')
        default: LUX_UNREACHABLE();
    }
}

SizeT get_real_sz($1 const& val) {
    switch(val.tag) {dnl
        m4_formember(`$@', `
        case $1::translit(member, `a-z', `A-Z'):
            return sizeof($1::Tag) + get_real_sz(val.member);')
        default: LUX_UNREACHABLE();
    }
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    if(deserialize(buff, buff_end, (U8*)&val->tag) != LUX_OK) {
        return LUX_FAIL;
    }
    switch(val->tag) {dnl
        m4_formember(`$@', `
        case $1::translit(member, `a-z', `A-Z'):
            return deserialize(buff, buff_end, &val->member);')
        default:
            LUX_LOG("unexpected packet tag %u", val->tag);
            return LUX_FAIL;
    }
}

void serialize(U8** buff, $1 const& val) {
    serialize(buff, (U8 const&)val.tag);
    switch(val.tag) {dnl
        m4_formember(`$@', `
        case $1::translit(member, `a-z', `A-Z'):
            serialize(buff, val.member); break;')
        default: LUX_UNREACHABLE();
    }
}dnl
',)')')dnl
')dnl
divert(0)dnl
#include <lux_shared/net/serial.hpp>
#include <lux_shared/net/data.hpp>

m4_lux_net_data(EntityComps::Shape, static, rad)
m4_lux_net_data(EntityComps::Visible, static, texture_id)
m4_lux_net_data(EntityComps::Item, static, weight)
m4_lux_net_data(EntityComps::Destructible, static, dur, dur_max)
m4_lux_net_data(EntityComps::Animated, static, time, time_max)
m4_lux_net_data(EntityComps, dynamic,
    pos, vel, shape, visible, item, destructible, animated)

m4_lux_net_data(NetSsInit, static, name, tick_rate)
m4_lux_net_data(NetSsTick, dynamic, player_id, comps)
m4_lux_net_data(NetSsSgnl::MapLoad::Chunk, static, voxels, light_lvls)
m4_lux_net_data(NetSsSgnl::MapLoad, dynamic, chunks)
m4_lux_net_data(NetSsSgnl::LightUpdate::Chunk, static, light_lvls)
m4_lux_net_data(NetSsSgnl::LightUpdate, dynamic, chunks)
m4_lux_net_data(NetSsSgnl::Msg, dynamic, contents)
m4_lux_net_data(NetSsSgnl, tagged, map_load, light_update, msg)
m4_lux_net_data(NetCsSgnl::MapRequest, dynamic, requests)
m4_lux_net_data(NetCsSgnl::Command, dynamic, contents)
m4_lux_net_data(NetCsSgnl, tagged, map_request, command)
m4_lux_net_data(NetCsInit, static,
    net_ver.major, net_ver.minor, net_ver.patch, name)
m4_lux_net_data(NetCsTick, static, player_dir)
