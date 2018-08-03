#pragma once

#include <cstddef>
#include <array>
//
#include <lux/alias/scalar.hpp>

template<typename T, std::size_t n>
using Array = std::array<T, n>;

namespace serial
{

class Serializer;
class Deserializer;

template<typename T, SizeT len>
SizeT get_size(Array<T, len> const &v);

template<typename T, SizeT len>
void clear_buffer(Array<T, len> &v);

template<typename T, SizeT len>
Serializer &operator<<(Serializer &in, Array<T, len> const &v);

template<typename T, SizeT len>
Deserializer &operator>>(Deserializer &out, Array<T, len> &v);

}
