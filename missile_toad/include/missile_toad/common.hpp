#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#if defined(_WIN32)
#    define NOGDI  // All GDI defines and routines
#    define NOUSER // All USER defines and routines
#endif
#include <spdlog/spdlog.h>

#if defined(_WIN32) // raylib uses these names as function parameters
#    undef near
#    undef far
#endif

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;

using std::ptrdiff_t;
using std::size_t;

namespace missiletoad
{
    /**
     * The update rate of the game.
     * This is used for fixed update.
     *
     * TODO: should this be a config option?
     */
    constexpr const float UPDATE_RATE = 1.0F / 60.0F;
} // namespace missiletoad

template <class T> inline void unused(const T &param) noexcept
{
    (void)param;
}
