#include "raylib-cpp.hpp"
#include "raylib.h"
#include <chrono>
#include <filesystem>
#include <fmt/format.h>
#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <physfs.h>
#include <spdlog/spdlog.h>

#include "missile_toad/common.hpp"
#include "missile_toad/game.hpp"

#ifdef PLATFORM_NX
#    include <switch.h>
#endif

unsigned char *load_file_data_callback(const char *file_name, unsigned int *bytes_read)
{
    PHYSFS_File *file = PHYSFS_openRead(file_name);
    if (file == nullptr)
    {
        return nullptr;
    }
    PHYSFS_sint64 size = PHYSFS_fileLength(file);
    auto         *data = gsl::owner<unsigned char *>(new unsigned char[size]);
    PHYSFS_readBytes(file, data, size);
    PHYSFS_close(file);
    *bytes_read = static_cast<unsigned int>(size);
    return data;
}

static constexpr int SCREEN_WIDTH  = 1280;
static constexpr int SCREEN_HEIGHT = 720;

void raylib_log_callback(int log_level, const char *format, va_list args)
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

int main(int argc, char *argv[]) noexcept(false)
{
    SetTraceLogCallback(raylib_log_callback);

#ifdef PLATFORM_NX
    romfsInit();
#endif
    int screen_width  = SCREEN_WIDTH;
    int screen_height = SCREEN_HEIGHT;

    spdlog::info("Initializing PhysFS.");
    if (PHYSFS_init(argv[0]) == 0)
    {
        return 1;
    }

    spdlog::info("Initializing audio device.");
    //    InitAudioDevice();

    spdlog::info("Setting PhysFS callbacks.");
    ::SetLoadFileDataCallback(load_file_data_callback);

    spdlog::info("Mounting romfs.");
    PHYSFS_mount("romfs:/", "/", 1);

    spdlog::info("Creating window of size {}x{}.", screen_width, screen_height);
    raylib::Window window(screen_width, screen_height, "raylib-cpp - basic window");

    auto current_time = std::chrono::high_resolution_clock::now();
    auto accumulator  = std::chrono::duration<float>(0);

    SetTargetFPS(60);

    // Init spdlog
    auto game = std::make_unique<missiletoad::Game>(argc, argv);

    while (!window.ShouldClose())
    {
        auto new_time   = std::chrono::high_resolution_clock::now();
        auto frame_time = new_time - current_time;
        current_time    = new_time;
        accumulator += frame_time;

        // We do this to guarantee that the fixed update is called at a fixed rate.
        // For instance, if the game is running at 60 FPS, and the fixed update rate is 30 FPS,
        // then the fixed update will be called every 2 frames.
        // But if the game is running at 30 FPS, then the fixed update will be called every frame.
        // To achieve this, we accumulate the time between frames, and call the fixed update
        // as many times as needed.
        while (accumulator >= std::chrono::duration<float>(missiletoad::UPDATE_RATE))
        {
            // FixedTick
            game->fixed_update(missiletoad::UPDATE_RATE);
            accumulator -= std::chrono::duration<float>(missiletoad::UPDATE_RATE);
        }

        // Tick
        auto delta_time = std::chrono::duration<float>(frame_time).count();
        game->update(delta_time);

        // Render
        game->render();
    }

    spdlog::info("Closing window.");

    if (PHYSFS_deinit() == 0)
    {
        spdlog::error("Failed to deinitialize PhysFS.");
        return 1;
    }

#ifdef PLATFORM_NX
    romfsExit();
#endif

    //    CloseAudioDevice();

    return 0;
}