#pragma once

#include <chrono>
#include <cstdint>
#include <gsl/gsl>
#include <memory>
#include <optional>
#include <string_view>
#include <utility>

#if defined(_WIN32)
#    define NOGDI  // All GDI defines and routines
#    define NOUSER // All USER defines and routines
#endif
#include "spdlog/spdlog.h"

#if defined(_WIN32) // raylib uses these names as function parameters
#    undef near
#    undef far
#    undef DELETE
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

namespace missiletoad::core
{
    /**
     * The update rate of the game.
     * This is used for fixed update.
     *
     * TODO: should this be a config option?
     */
    constexpr const float UPDATE_RATE = 1.0F / 60.0F;

    /**
     * The number of pixels per unit.
     */
    constexpr auto PIXELS_PER_UNIT = 64.0F;

    /**
     * The scale of the physics engine.
     */
    constexpr auto PHYSICS_SCALE = 0.5F;

    // NOLINTNEXTLINE(*-avoid-c-arrays)
    std::optional<std::pair<std::unique_ptr<uint8_t[]>, size_t>> load_file(std::string_view name);
} // namespace missiletoad::core

template <typename... Args>
// NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
constexpr void unused([[maybe_unused]] Args &&...args) noexcept
{
}

enum class EFloatCompare
{
    LESS_THAN,
    EQUAL,
    GREATER_THAN,
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
constexpr EFloatCompare compare_float(float lhs, float rhs, float epsilon = 0.001F)
{
    if (lhs + epsilon < rhs)
    {
        return EFloatCompare::LESS_THAN;
    }
    if (lhs - epsilon > rhs)
    {
        return EFloatCompare::GREATER_THAN;
    }
    return EFloatCompare::EQUAL;
}
