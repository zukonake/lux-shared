#pragma once

#include <lux_shared/containers.hpp>

///example: "bob"_l is a Str
constexpr Slice<const char> operator"" _l(const char* cstr, SizeT len) {
    return {cstr, len};
}

typedef Slice<const char> Str;
typedef Slice<char>       DynStr;
typedef DynArr<char>      StrBuff;
