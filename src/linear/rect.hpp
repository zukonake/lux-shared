#pragma once

#include <linear/point_2d.hpp>

namespace linear
{

template<typename T>
struct Rect
{
    Point2d<T> tl; //top-left
    Point2d<T> br; //bottom-right
};

}
