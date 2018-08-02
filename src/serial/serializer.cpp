#include <cstdlib>
#include <cassert>
#include <stdexcept>
//
#include <lux/serial/serializer.hpp>

namespace serial
{

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

}
