#include "raylib-cpp.hpp"
#include "raylib.h"
#include <filesystem>
#include <fmt/format.h>
#include <gsl/gsl>
#include <iostream>
#include <physfs.h>

#ifdef PLATFORM_NX
#    include <switch.h>
#endif

#ifdef WIN32
#    pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

unsigned char *load_file_data_callback(const char *fileName, unsigned int *bytesRead)
{
    PHYSFS_File *file = PHYSFS_openRead(fileName);
    if (file == nullptr)
    {
        return nullptr;
    }
    PHYSFS_sint64 size = PHYSFS_fileLength(file);
    auto         *data = gsl::owner<unsigned char *>(new unsigned char[size]);
    PHYSFS_readBytes(file, data, size);
    PHYSFS_close(file);
    *bytesRead = size;
    return data;
}

int main(int argc, char *argv[])
{
#ifdef PLATFORM_NX
    romfsInit();
#endif
    int screenWidth  = 1280;
    int screenHeight = 720;

    // NO-LINT
    if (PHYSFS_init(argv[0]) == 0)
    {
        return 1;
    }

    ::SetLoadFileDataCallback(load_file_data_callback);

    PHYSFS_mount("romfs:/", "/", 1);
    raylib::Window window(screenWidth, screenHeight, "raylib-cpp - basic window");

    raylib::Texture2D texture("/resources/raylib_logo.png");

    raylib::Camera2D camera({0, 0}, {0, 0}, 0, 1);

    while (!window.ShouldClose())
    {
        window.ClearBackground(RAYWHITE);
        EndDrawing();
    }

    // UnloadTexture() and CloseWindow() are called automatically.

#ifdef PLATFORM_NX
    romfsExit();
#endif

    return 0;
}