#pragma once

#include <cstdlib>
#include <cassert>
//
#include <lux/alias/scalar.hpp>
#include <lux/net/net_order.hpp>
#include <lux/serial/get_size.hpp>
#include <lux/serial/clear_buffer.hpp>

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

template<typename T>
inline void serialize(Serializer &in, T &buf)
{
    in.reserve(serial::get_size(buf));
    in << buf;
    serial::clear_buffer(buf);
}

inline Serializer::Serializer() :
    start(nullptr),
    iter(nullptr),
    end(nullptr)
{

}

inline Serializer::~Serializer()
{
    if(start != nullptr) std::free(start);
}

inline U8 const *Serializer::get() const
{
    return start;
}

inline SizeT Serializer::get_free() const
{
    return end - iter;
}

inline SizeT Serializer::get_used() const
{
    return iter - start;
}

inline SizeT Serializer::get_size() const
{
    return end - start;
}

inline Serializer &operator<<(Serializer &in, U8 const &v)
{
    assert(in.get_free() >= 1);
    *in.iter = v;
    in.iter += 1;
    return in;
}

inline Serializer &operator<<(Serializer &in, U16 const &v)
{
    assert(in.get_free() >= 2);
    net::net_memcpy(in.iter, (U8 *)&v, 2);
    in.iter += 2;
    return in;
}

inline Serializer &operator<<(Serializer &in, U32 const &v)
{
    assert(in.get_free() >= 4);
    net::net_memcpy(in.iter, (U8 *)&v, 4);
    in.iter += 4;
    return in;
}

inline Serializer &operator<<(Serializer &in, U64 const &v)
{
    assert(in.get_free() >= 8);
    net::net_memcpy(in.iter, (U8 *)&v, 8);
    in.iter += 8;
    return in;
}

inline Serializer &operator<<(Serializer &in, I8 const &v)
{
    in << *((U8 const *)&v);
    return in;
}

inline Serializer &operator<<(Serializer &in, I16 const &v)
{
    in << *((U16 const *)&v);
    return in;
}

inline Serializer &operator<<(Serializer &in, I32 const &v)
{
    in << *((U32 const *)&v);
    return in;
}

inline Serializer &operator<<(Serializer &in, I64 const &v)
{
    in << *((U64 const *)&v);
    return in;
}

inline Serializer &operator<<(Serializer &in, bool const &v)
{
    in << *((U8 const *)&v);
    return in;
}

inline Serializer &operator<<(Serializer &in, char const &v)
{
    in << *((U8 const *)&v);
    return in;
}

inline Serializer &operator<<(Serializer &in, F32 const &v)
{
    in << *((U32 const *)&v);
    return in;
}

inline Serializer &operator<<(Serializer &in, F64 const &v)
{
    in << *((U64 const *)&v);
    return in;
}

}
