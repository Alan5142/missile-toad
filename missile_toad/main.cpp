/// @file missile_toad/main.cpp

#include <chrono>
#include <fmt/format.h>
#include <gsl/gsl>
#include <memory>
#include <raylib.h>

#include "missile_toad/core/common.hpp"
#include "missile_toad/game.hpp"

#ifdef PLATFORM_NX
#    include <switch.h>
#endif

/**
 * The callback function for raylib's logging system. It forwards the log to spdlog.
 * @param log_level log level
 * @param format format string
 * @param args format arguments
 */
static void raylib_log_callback(int log_level, const char *format, va_list args)
{
    constexpr size_t              buffer_size = 4096;
    std::array<char, buffer_size> buffer{};
    vsnprintf(buffer.data(), sizeof(buffer), format, args);
    switch (log_level)
    {
    case LOG_INFO:
        spdlog::info(buffer.data());
        break;
    case LOG_ERROR:
        spdlog::error(buffer.data());
        break;
    case LOG_WARNING:
        spdlog::warn(buffer.data());
        break;
    case LOG_DEBUG:
        spdlog::debug(buffer.data());
        break;
    case LOG_TRACE:
        spdlog::trace(buffer.data());
        break;
    case LOG_FATAL:
        spdlog::critical(buffer.data());
        break;
    default:
        break;
    }
}

/**
 * The entry point of the game.
 * @param argc argument count
 * @param argv argument vector
 * @return the exit code of the game
 */
int main(int argc, char *argv[]) noexcept(false)
{
    SetTraceLogCallback(raylib_log_callback);

    spdlog::set_level(spdlog::level::trace);

#ifdef PLATFORM_NX
    romfsInit();
#endif
    InitAudioDevice();
    auto game = std::make_unique<missiletoad::Game>(argc, argv);

    game->run();

    spdlog::info("Game ended.");
    CloseAudioDevice();
#ifdef PLATFORM_NX
    romfsExit();
#endif

    return 0;
}
