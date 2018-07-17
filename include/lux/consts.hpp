#pragma once

#include <lux/common/chunk.hpp>

namespace consts
{

constexpr ChunkSize CHUNK_SIZE = {16, 16, 3};
constexpr SizeT     CHUNK_TILE_SIZE = CHUNK_SIZE.x * CHUNK_SIZE.y * CHUNK_SIZE.z;

}
