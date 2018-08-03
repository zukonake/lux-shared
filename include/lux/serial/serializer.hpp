#pragma once

#include <lux/alias/scalar.hpp>

namespace serial
{

class Serializer
{
    public:
    Serializer();
    ~Serializer();

    friend Serializer &operator<<(Serializer &in, U8  const &v);
    friend Serializer &operator<<(Serializer &in, U16 const &v);
    friend Serializer &operator<<(Serializer &in, U32 const &v);
    friend Serializer &operator<<(Serializer &in, U64 const &v);

    U8 const *get() const;
    SizeT get_free() const;
    SizeT get_used() const;
    SizeT get_size() const;
    void reserve(SizeT n_bytes);

    private:
    U8 *start;
    U8 *iter;
    U8 *end;
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
Serializer &operator<<(Serializer &in, char const &v);
Serializer &operator<<(Serializer &in, F32 const &v);
Serializer &operator<<(Serializer &in, F64 const &v);

}
