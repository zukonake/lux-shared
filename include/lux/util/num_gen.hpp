#pragma once

#include <random>

namespace util
{

class NumGen : std::mt19937
{
    public:
    NumGen(std::mt19937::result_type const &seed);

    using std::mt19937::operator();

    void seed(std::mt19937::result_type const &seed);
};

}
