#include "deserializer.hpp"

namespace net
{

Deserializer::Deserializer(U8 const *arr, U8 const *end) :
    arr(arr),
    end(end)
{

}

SizeT Deserializer::get_size() const
{
    return (SizeT)(end - arr);
}

}

