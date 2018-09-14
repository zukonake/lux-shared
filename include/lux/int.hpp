#pragma once

#include <cstdint>

typedef std::uint8_t  U8;
typedef std::uint16_t U16;
typedef std::uint32_t U32;
typedef std::uint64_t U64;

typedef std::int8_t   I8;
typedef std::int16_t  I16;
typedef std::int32_t  I32;
typedef std::int64_t  I64;

typedef float         F32;
typedef double        F64;

typedef std::size_t   SizeT;

//@CONSIDER moving those to places that need those assumptions
static_assert(sizeof(F32) == 4);
static_assert(sizeof(F64) == 8);
static_assert(sizeof(SizeT) >= 8);

typedef std::int_fast32_t  Int;
typedef std::uint_fast32_t Uns;
