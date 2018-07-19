#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/linear/vec_3.hpp>
#include <lux/common/map.hpp>

namespace chunk
{

typedef I32 Coord;
typedef linear::Vec3<Coord> Pos;
typedef linear::Vec3<U16>   Size;
typedef SizeT Index;

Pos      to_pos  (map::Pos const &pos);
Index    to_index(map::Pos const &pos);
map::Pos to_map_pos(chunk::Pos const &pos, chunk::Index const &idx);

constexpr Size  SIZE = {16, 16, 3};
constexpr SizeT TILE_SIZE = SIZE.x * SIZE.y * SIZE.z;

}
