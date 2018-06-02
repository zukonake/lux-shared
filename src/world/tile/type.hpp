#pragma once

#include <cstdint>
//
#include <linear/point_2d.hpp>

namespace world::tile
{

struct Type
{
    enum Shape : uint8_t
    {
        EMPTY,
        FLOOR,
        WALL
    };

    Type(Shape shape, linear::Point2d<uint8_t> tex_pos);

    Shape shape;
    linear::Point2d<uint8_t> tex_pos; //TODO typedef?
};

}
