#include <lux_shared/util/clock.hpp>

namespace util
{

Clock::Clock() :
    before(clock.now())
{

}

void Clock::start()
{
    before = clock.now();
}

typename Clock::Duration Clock::stop()
{
    return Duration(clock.now() - before);
}

}
