#pragma once

#include <cassert>
//
#include <lux/alias/scalar.hpp>
#include <lux/alias/vector.hpp>
#include <lux/alias/array.hpp>

namespace serial
{

class Serializer
{
    public:
    friend Serializer &operator<<(Serializer &in, U8    const &v);
    friend Serializer &operator<<(Serializer &in, U16   const &v);
    friend Serializer &operator<<(Serializer &in, U32   const &v);
    friend Serializer &operator<<(Serializer &in, U64   const &v);

    Vector<U8> const &get() const;
    void clear();

    private:
    Vector<U8> storage;
};

Serializer &operator<<(Serializer &in, U8 const &v);
Serializer &operator<<(Serializer &in, U16 const &v);
Serializer &operator<<(Serializer &in, U32 const &v);
Serializer &operator<<(Serializer &in, U64 const &v);

Serializer &operator<<(Serializer &in, I8 const &v);
Serializer &operator<<(Serializer &in, I16 const &v);
Serializer &operator<<(Serializer &in, I32 const &v);
Serializer &operator<<(Serializer &in, I64 const &v);

Serializer &operator<<(Serializer &in, bool const &v);
Serializer &operator<<(Serializer &in, F32 const &v);
Serializer &operator<<(Serializer &in, F64 const &v);

}
