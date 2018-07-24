#include <cstdlib>
#include <cassert>
#include <stdexcept>
//
#include <lux/net/net_order.hpp>
#include <lux/serial/serializer.hpp>

namespace serial
{

Serializer::Serializer() :
    start(nullptr),
    iter(nullptr),
    end(nullptr)
{

}

Serializer::~Serializer()
{
    if(start != nullptr) std::free(start);
}

U8 const *Serializer::get() const
{
    return start;
}

SizeT Serializer::get_free() const
{
    return end - iter;
}

SizeT Serializer::get_size() const
{
    return end - start;
}

void Serializer::reserve(SizeT n_bytes)
{
    if(start == nullptr || get_size() < n_bytes)
    {
        U8 *new_start = nullptr;
        if(start == nullptr)
        {
            new_start = (U8 *)std::malloc(n_bytes);
        }
        else
        {
            new_start = (U8 *)std::realloc(start, n_bytes);
            //TODO experiment with exponential allocation
        }
        if(new_start == nullptr) throw std::bad_alloc();
        else start = new_start;

        end = start + n_bytes;
    }
    iter = start;
}

Serializer &operator<<(Serializer &in, U8 const &v)
{
    assert(in.get_free() >= 1);
    *in.iter = v;
    in.iter += 1;
    return in;
}

Serializer &operator<<(Serializer &in, U16 const &v)
{
    assert(in.get_free() >= 2);
    net::net_memcpy(in.iter, (U8 *)&v, 2);
    in.iter += 2;
    return in;
}

Serializer &operator<<(Serializer &in, U32 const &v)
{
    assert(in.get_free() >= 4);
    net::net_memcpy(in.iter, (U8 *)&v, 4);
    in.iter += 4;
    return in;
}

Serializer &operator<<(Serializer &in, U64 const &v)
{
    assert(in.get_free() >= 8);
    net::net_memcpy(in.iter, (U8 *)&v, 8);
    in.iter += 8;
    return in;
}

Serializer &operator<<(Serializer &in, I8 const &v)
{
    in << *((U8 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, I16 const &v)
{
    in << *((U16 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, I32 const &v)
{
    in << *((U32 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, I64 const &v)
{
    in << *((U64 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, bool const &v)
{
    in << *((U8 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, char const &v)
{
    in << *((U8 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, F32 const &v)
{
    in << *((U32 const *)&v);
    return in;
}

Serializer &operator<<(Serializer &in, F64 const &v)
{
    in << *((U64 const *)&v);
    return in;
}

}
