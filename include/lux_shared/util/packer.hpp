#pragma once

#include <lux_shared/int.hpp>
#include <lux_shared/vec.hpp>

namespace util
{

template<typename T>
struct Packer
{
    SizeT operator()(T const &);
};

#if defined(LUX_64BIT)
template<typename T>
struct Packer<Vec2<T>> {
    SizeT operator()(Vec2<T> const& v) const {
        return  (v.x & 0xFFFF'FFFF) |
               ((v.y & 0xFFFF'FFFF) << 32);
    }
};

template<typename T>
struct Packer<Vec3<T>> {
    SizeT operator()(Vec3<T> const& v) const {
        return  (v.x & 0xFFFFF) |
               ((v.y & 0xFFFFF) << 20) |
               ((v.z & 0xFFFFF) << 40);
    }
};

template<typename T>
struct Packer<Vec4<T>> {
    SizeT operator()(Vec4<T> const& v) const {
        return  (v.x & 0xFFFF) |
               ((v.y & 0xFFFF) << 16) |
               ((v.z & 0xFFFF) << 32) |
               ((v.w & 0xFFFF) << 48);
    }
};
#elif defined(LUX_32BIT)
template<typename T>
struct Packer<Vec2<T>> {
    SizeT operator()(Vec2<T> const& v) const {
        return  (v.x & 0xFFFF) |
               ((v.y & 0xFFFF) << 16);
    }
};

template<typename T>
struct Packer<Vec3<T>> {
    SizeT operator()(Vec3<T> const& v) const {
        return  (v.x & 0x3FF) |
               ((v.y & 0x3FF) << 10) |
               ((v.z & 0x3FF) << 20);
    }
};

template<typename T>
struct Packer<Vec4<T>> {
    SizeT operator()(Vec4<T> const& v) const {
        return  (v.x & 0xFF) |
               ((v.y & 0xFF) << 8) |
               ((v.z & 0xFF) << 16) |
               ((v.w & 0xFF) << 24);
    }
};
#endif

}
