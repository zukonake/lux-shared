#pragma once

#include <alias/int.hpp>
#include <linear/point_2d.hpp>
#include <net/serialize.hpp>
#include <net/deserialize.hpp>

namespace net
{

#pragma pack(push, 1)
struct TileState
{
    typedef linear::Point2d<U8> TexPos;
    enum Shape : U8
    {
        EMPTY,
        FLOOR,
        WALL
    };

    Shape shape;
    TexPos tex_pos;
};
#pragma pack(pop)

template<>
inline void serialize<TileState>(Vector<U8> &bytes, TileState const &val)
{
    serialize<U8>(bytes, (U8)val.shape);
    serialize<U8>(bytes, val.tex_pos.x);
    serialize<U8>(bytes, val.tex_pos.y);
}

template<>
inline void deserialize<TileState>(Vector<U8> &bytes, TileState &val)
{
    deserialize<U8>(bytes, (U8 &)val.shape);
    deserialize<U8>(bytes, val.tex_pos.x);
    deserialize<U8>(bytes, val.tex_pos.y);
}

}
