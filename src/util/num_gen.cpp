#include <lux/util/num_gen.hpp>

namespace util
{

NumGen::NumGen(std::mt19937::result_type const &seed)
{
	std::mt19937::seed(seed);
}

void NumGen::seed(std::mt19937::result_type const &seed)
{
	std::mt19937::seed(seed);
}

}
