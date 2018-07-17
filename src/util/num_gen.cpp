#include <lux/util/num_gen.hpp>

namespace util
{

NumGen::NumGen()
{
	std::random_device randomDevice;
	std::mt19937::seed(randomDevice());
}

NumGen::NumGen(std::mt19937::result_type const &seed)
{
	std::mt19937::seed(seed);
}

void NumGen::default_seed()
{
	std::random_device randomDevice;
	std::mt19937::seed(randomDevice());
}

void NumGen::seed(std::mt19937::result_type const &seed)
{
	std::mt19937::seed(seed);
}

NumGen numGen;

}
