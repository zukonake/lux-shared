#pragma once

#include <lux_shared/common.hpp>

typedef struct {
   Vec3F p[3];
} Triangle;

typedef struct {
   Vec3F p[8];
   F32 val[8];
} GridCell;

int polygonise(GridCell grid, F32 isolevel, Triangle *triangles);
