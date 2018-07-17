#pragma once

#include <lux/alias/scalar.hpp>
#include <lux/linear/vec_3.hpp>
#include <lux/common/map.hpp>

typedef I32 ChunkCoord;
typedef linear::Vec3<ChunkCoord> ChunkPos;
typedef linear::Vec3<U16>        ChunkSize;
typedef SizeT ChunkIndex;

ChunkPos   to_chunk_pos(MapPos const &pos);
ChunkIndex to_chunk_index(MapPos const &pos);
