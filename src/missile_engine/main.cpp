/// @file missile_toad/main.cpp

#include <chrono>
#include <fmt/format.h>
#include <fstream>
#include <gsl/gsl>
#include <memory>
#include <raylib.h>

#include "missile_engine/common.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/game_descriptor.hpp"

#ifdef PLATFORM_NX
#    include <switch.h>
#endif

#ifdef PLATFORM_NX
constexpr std::string_view GAME_METADATA = "romfs:/game.json";
#else
constexpr std::string_view GAME_METADATA = "game.json";
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

#ifdef PLATFORM_NX
    romfsInit();
#endif

    InitAudioDevice();

    auto game_json = std::ifstream(GAME_METADATA.data());
    if (!game_json.is_open())
    {
        spdlog::error("Failed to open game.json.");
        throw std::runtime_error("Failed to open game.json.");
    }

    // Read all contents of the file into a string.
    std::string game_json_str((std::istreambuf_iterator<char>(game_json)), std::istreambuf_iterator<char>());
    auto        game_descriptor_opt = missilengine::load_game_descriptor(game_json_str);
    if (!game_descriptor_opt.has_value())
    {
        spdlog::error("Failed to load game.json.");
        return 1;
    }

    std::vector<std::string_view> arguments;
    arguments.reserve(argc);
    for (auto i = 0; i < argc; i++)
    {
        spdlog::debug("argv[{}] = {}", i, argv[i]);
        arguments.emplace_back(argv[i]);
    }

    try
    {
        auto game = std::make_unique<missilengine::Game>(std::move(arguments), game_descriptor_opt.value());
        game->run();
    }
    catch (const std::exception &e)
    {
        spdlog::error("An exception occurred: {}", e.what());
        return 1;
    }

    spdlog::info("Game ended.");

    CloseAudioDevice();

#ifdef PLATFORM_NX
    romfsExit();
#endif

    return 0;
}
