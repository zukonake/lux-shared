#pragma once

namespace util
{

template<typename T>
T merge_hash(T a, T b)
{
    return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
}

}
