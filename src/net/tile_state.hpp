#pragma once

#include <alias/int.hpp>
#include <linear/point_2d.hpp>

namespace net
{

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
    TileState(Shape shape, TexPos tex_pos);
};

}
