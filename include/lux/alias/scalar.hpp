#pragma once

#include <cstddef>
#include <cstdint>

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

typedef int8_t   I8;
typedef int16_t  I16;
typedef int32_t  I32;
typedef int64_t  I64;

typedef float    F32;
typedef double   F64;

typedef int_fast32_t  Int;
typedef uint_fast32_t UInt;

typedef std::size_t SizeT;

static_assert(sizeof(F32) == 4);
static_assert(sizeof(F64) == 8);
