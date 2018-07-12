#include "serializer.hpp"

namespace net
{

Serializer::Serializer(SizeT len) :
    iter(0),
    arr(new U8[len])
{
    
}

Serializer::~Serializer()
{
    delete[] arr;
}

SizeT Serializer::get_size() const
{
    return iter;
}

U8 *Serializer::get() const
{
    return arr;
}

}
