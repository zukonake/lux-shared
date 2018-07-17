#pragma once

namespace util
{

template<typename T>
T merge_hash(T a, T b)
{
    return a * 0x7FFFFFFF + b;
}

}
