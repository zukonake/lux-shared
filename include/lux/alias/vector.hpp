#pragma once

#include <vector>
//
#include <lux/alias/scalar.hpp>

template<typename T>
using Vector = std::vector<T>;

namespace serial
{

class Serializer;
class Deserializer;

template<typename T>
SizeT get_size(Vector<T> const &v);

template<typename T>
void clear_buffer(Vector<T> &v);

template<typename T>
Serializer &operator<<(Serializer &in, Vector<T> const &v);

template<typename T>
Deserializer &operator>>(Deserializer &out, Vector<T> &v);

}
