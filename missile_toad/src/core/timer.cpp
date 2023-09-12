#include "missile_toad/core/timer.hpp"

missiletoad::core::Timer::Timer(std::function<void()> callback) : callback_(std::move(callback))
{
}
