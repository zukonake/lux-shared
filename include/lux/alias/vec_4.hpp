#pragma once

#include <functional>
//
#include <glm/detail/type_vec4.hpp>
//
#include <lux/alias/scalar.hpp>
#include <lux/util/merge_hash.hpp>
#include <lux/util/packer.hpp>

template<typename T>
using Vec4 = glm::tvec4<T>;

typedef Vec4<U16> Vec4US;
typedef Vec4<U32> Vec4UI;
typedef Vec4<I16> Vec4S;
typedef Vec4<I32> Vec4I;
typedef Vec4<I64> Vec4L;
typedef Vec4<F32> Vec4F;
typedef Vec4<F64> Vec4D;

template<typename T>
struct std::hash<Vec4<T>>
{
    SizeT operator()(Vec4<T> const &k) const
    {
        return util::merge_hash(std::hash<T>()(k.x),
               util::merge_hash(std::hash<T>()(k.y),
               util::merge_hash(std::hash<T>()(k.z), std::hash<T>()(k.w))));
    }
};

template<typename T>
struct util::Packer<Vec4<T>>
{
    SizeT operator()(Vec4<T> const &k) const
    {
        return  ((SizeT)k.w           << 48) |
               (((SizeT)k.z & 0xFFFF) << 32) |
               (((SizeT)k.y & 0xFFFF) << 16) |
                ((SizeT)k.x & 0xFFFF);
    }
};

/* no serializing implemented unless it's needed */
