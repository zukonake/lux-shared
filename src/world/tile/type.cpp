#include "type.hpp"

namespace world::tile
{

Type::Type(Shape shape, linear::Point2d<uint8_t> tex_pos) :
    shape(shape),
    tex_pos(tex_pos)
{

}

}
