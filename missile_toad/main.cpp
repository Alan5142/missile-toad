#include "raylib-cpp.hpp"
#include "raylib.h"
#include <chrono>
#include <filesystem>
#include <fmt/format.h>
#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <physfs.h>

#include "missile_toad/common.hpp"
#include "missile_toad/game.hpp"

#ifdef PLATFORM_NX
#    include <switch.h>
#endif

#ifdef WIN32
#    pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
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

int main(int argc, char *argv[]) noexcept(false)
{
#ifdef PLATFORM_NX
    romfsInit();
#endif
    int screen_width  = SCREEN_WIDTH;
    int screen_height = SCREEN_HEIGHT;

    if (PHYSFS_init(argv[0]) == 0)
    {
        return 1;
    }

    ::SetLoadFileDataCallback(load_file_data_callback);

    PHYSFS_mount("romfs:/", "/", 1);
    raylib::Window window(screen_width, screen_height, "raylib-cpp - basic window");

    auto current_time = std::chrono::high_resolution_clock::now();
    auto accumulator  = std::chrono::duration<float>(0);

    auto game = std::make_unique<missiletoad::Game>(argc, argv);

    raylib::Music music = raylib::Music("romfs:/resources/Maxwell.mp3");

    music.Play();

    SetTargetFPS(60);

    while (!window.ShouldClose())
    {
        auto new_time   = std::chrono::high_resolution_clock::now();
        auto frame_time = new_time - current_time;
        current_time    = new_time;
        accumulator += frame_time;

        while (accumulator >= std::chrono::duration<float>(missiletoad::UPDATE_RATE))
        {
            // FixedTick
            game->fixed_update(missiletoad::UPDATE_RATE);
            accumulator -= std::chrono::duration<float>(missiletoad::UPDATE_RATE);
        }

        // Tick
        auto delta_time = std::chrono::duration<float>(frame_time).count();
        game->update(delta_time);
        music.Update();

        // Render
        game->render();
    }

#ifdef PLATFORM_NX
    romfsExit();
#endif

    return 0;
}