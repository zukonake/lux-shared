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
void clear_net_data($1* val) {
    m4_foreach(`member', `shift(shift($@))', `
    clear_net_data(&val->member);')
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    LUX_RETHROW(buff_sz_at_least(sizeof($1), *buff, buff_end));dnl
    m4_foreach(`member', `shift(shift($@))', `
    (void)deserialize(buff, buff_end, &val->member);')
    return LUX_OK;
}

void serialize(U8** buff, $1 const& val) {dnl
    m4_foreach(`member', `shift(shift($@))', `
    serialize(buff, val.member);')
}', `dnl
dnl
dnl
ifelse(`$2', `dynamic', `dnl

void clear_net_data($1* val) {
    m4_foreach(`member', `shift(shift($@))', `
    clear_net_data(&val->member);')
}

SizeT get_real_sz($1 const& val) {
    return m4_foreach(`member', `shift(shift($@))', `
        get_real_sz(val.member) +')
        0;
}

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
    m4_foreach(`member', `shift(shift($@))', `
    LUX_RETHROW(deserialize(buff, buff_end, &val->member),
                "failed to deserialize member of $1");')
    return LUX_OK;
}

void serialize(U8** buff, $1 const& val) {dnl
    m4_foreach(`member', `shift(shift($@))', `
    serialize(buff, val.member);')
}', `dnl
dnl
dnl
ifelse(`$2', `tagged', `dnl

void clear_net_data($1* val) {
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

SizeT get_real_sz($1 const& val) {
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

LUX_MAY_FAIL deserialize(U8 const** buff, U8 const* buff_end, $1* val) {
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

void serialize(U8** buff, $1 const& val) {
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
#include <lux_shared/net/serial.hpp>
#include <lux_shared/net/data.hpp>

m4_lux_net_data(NetSsInit, static, name, tick_rate)
m4_lux_net_data(NetSsTick::DbgInf::Shape::Point, static, pos)
m4_lux_net_data(NetSsTick::DbgInf::Shape::Line, static, beg, end)
m4_lux_net_data(NetSsTick::DbgInf::Shape::Arrow, static, beg, end)
m4_lux_net_data(NetSsTick::DbgInf::Shape::Cross, static, pos, sz)
m4_lux_net_data(NetSsTick::DbgInf::Shape::Sphere, static, pos, rad)
m4_lux_net_data(NetSsTick::DbgInf::Shape::Triangle, static, verts)
m4_lux_net_data(NetSsTick::DbgInf::Shape::Rect, static, pos, sz, angle)
m4_lux_net_data(NetSsTick::DbgInf::Shape, tagged, `point, line, arrow,
    cross, sphere, triangle, rect', col, border)
m4_lux_net_data(NetSsTick::DbgInf, dynamic, shapes)
m4_lux_net_data(NetSsTick::EntityComps::Visible, static, visible_id, quad_sz)
m4_lux_net_data(NetSsTick::EntityComps::Item, static, weight)
m4_lux_net_data(NetSsTick::EntityComps::Container, dynamic, items)
m4_lux_net_data(NetSsTick::EntityComps::Orientation, static, angle)
m4_lux_net_data(NetSsTick::EntityComps, dynamic,
    pos, name, visible, item, container, orientation)
m4_lux_net_data(NetSsTick, dynamic, day_cycle, player_id, entity_comps, dbg_inf,
    entities)
m4_lux_net_data(NetSsSgnl::Tiles::Chunk, static, floor, wall, roof)
m4_lux_net_data(NetSsSgnl::Tiles, dynamic, chunks)
m4_lux_net_data(NetSsSgnl::Light::Chunk, static, light_lvl)
m4_lux_net_data(NetSsSgnl::Light, dynamic, chunks)
m4_lux_net_data(NetSsSgnl::Msg, dynamic, contents)
m4_lux_net_data(NetSsSgnl, tagged, `tiles, light, msg')
m4_lux_net_data(NetCsSgnl::MapRequest, dynamic, requests)
m4_lux_net_data(NetCsSgnl::Command, dynamic, contents)
m4_lux_net_data(NetCsSgnl::Action, dynamic, bytecode)
m4_lux_net_data(NetCsSgnl, tagged, `map_request, command', actions)
m4_lux_net_data(NetCsInit, static,
    net_ver.major, net_ver.minor, net_ver.patch, name)
m4_lux_net_data(NetCsTick::Action, dynamic, bytecode)
m4_lux_net_data(NetCsTick, dynamic, actions)
