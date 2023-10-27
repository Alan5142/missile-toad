/// @file missile_toad/src/core/asset_manager.cpp

#include "missile_engine/asset_manager.hpp"
#include "physfs.h"

#include <filesystem>

#if defined(PLATFORM_NX)
static constexpr std::string_view PREFERENCES_PATH = "sdmc:/missiletoad.preferences";
#else
static constexpr std::string_view PREFERENCES_PATH = "preferences";
#endif

static constexpr std::string_view PREFERENCES_PATH_MOUNT_POINT = "/preferences";

missilengine::AssetManager::AssetManager()
{
    spdlog::trace("AssetManager::AssetManager() called.");

    // Init PhysFS
    if (PHYSFS_init(nullptr) == 0)
    {
        spdlog::error("Failed to init PhysFS: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to init PhysFS");
    }
    spdlog::trace("PhysFS initialized.");

    // Create the preferences directory if it doesn't exist.
    if (!std::filesystem::exists(PREFERENCES_PATH.data()))
    {
        if (!std::filesystem::create_directory(PREFERENCES_PATH.data()))
        {
            spdlog::error("Failed to create preferences directory: {}",
                          PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
            throw std::runtime_error("Failed to create preferences directory");
        }
    }

    // Mount the preferences directory, first creating it if it doesn't exist.
    if (PHYSFS_mount(PREFERENCES_PATH.data(), PREFERENCES_PATH_MOUNT_POINT.data(), 0) == 0)
    {
        spdlog::error("Failed to mount preferences directory: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to mount preferences directory");
    }

    spdlog::trace("AssetManager::AssetManager() finished.");
}

missilengine::AssetManager::~AssetManager()
{
    spdlog::trace("AssetManager::~AssetManager() called.");
    PHYSFS_deinit();
    spdlog::trace("PhysFS deinitialized.");
    spdlog::trace("AssetManager::~AssetManager() finished.");
}

void missilengine::AssetManager::push_asset_folder(std::string_view path, std::string_view mount_point)
{
    spdlog::trace("AssetManager::push_asset_folder() called.");
    if (PHYSFS_mount(path.data(), mount_point.data(), 0) == 0)
    {
        spdlog::error("Failed to mount assets directory: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to mount assets directory");
    }
    spdlog::trace("AssetManager::push_asset_folder() finished.");
}

void missilengine::AssetManager::pop_asset_folder(std::string_view mount_point)
{
    spdlog::trace("AssetManager::pop_asset_folder() called.");
    if (PHYSFS_unmount(mount_point.data()) == 0)
    {
        spdlog::error("Failed to unmount assets directory: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to unmount assets directory");
    }
    spdlog::trace("AssetManager::pop_asset_folder() finished.");
}
