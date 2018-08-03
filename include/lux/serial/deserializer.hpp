#pragma once

#include <cassert>
//
#include <lux/alias/scalar.hpp>

namespace serial
{

class Deserializer
{
    public:
    void set_slice(U8 const *start, U8 const *end);

    friend Deserializer &operator>>(Deserializer &out, U8  &v);
    friend Deserializer &operator>>(Deserializer &out, U16 &v);
    friend Deserializer &operator>>(Deserializer &out, U32 &v);
    friend Deserializer &operator>>(Deserializer &out, U64 &v);

    SizeT get_size() const;

    private:
    U8 const *iter;
    U8 const *end;
};

Deserializer &operator>>(Deserializer &out, U8 &v);
Deserializer &operator>>(Deserializer &out, U16 &v);
Deserializer &operator>>(Deserializer &out, U32 &v);
Deserializer &operator>>(Deserializer &out, U64 &v);

Deserializer &operator>>(Deserializer &out, I8 &v);
Deserializer &operator>>(Deserializer &out, I16 &v);
Deserializer &operator>>(Deserializer &out, I32 &v);
Deserializer &operator>>(Deserializer &out, I64 &v);
Deserializer &operator>>(Deserializer &out, bool &v);
Deserializer &operator>>(Deserializer &out, char &v);
Deserializer &operator>>(Deserializer &out, F32 &v);
Deserializer &operator>>(Deserializer &out, F64 &v);

}
