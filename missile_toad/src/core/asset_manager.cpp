#include "missile_toad/core/asset_manager.hpp"
#include "physfs.h"

#include <filesystem>

#if defined(PLATFORM_NX)
static constexpr std::string_view ASSETS_PATH      = "romfs:/assets";
static constexpr std::string_view PREFERENCES_PATH = "sdmc:/missiletoad.preferences";
#else
static constexpr std::string_view ASSETS_PATH      = "missiletoad.assets";
static constexpr std::string_view PREFERENCES_PATH = "preferences";
#endif

static constexpr std::string_view ASSETS_PATH_MOUNT_POINT      = "/assets";
static constexpr std::string_view PREFERENCES_PATH_MOUNT_POINT = "/preferences";

missiletoad::core::AssetManager::AssetManager()
{
    spdlog::trace("AssetManager::AssetManager() called.");

    // Init PhysFS
    if (PHYSFS_init(nullptr) == 0)
    {
        spdlog::error("Failed to init PhysFS: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to init PhysFS");
    }
    spdlog::trace("PhysFS initialized.");

    // Mount the base directory
    if (PHYSFS_mount(ASSETS_PATH.data(), ASSETS_PATH_MOUNT_POINT.data(), 0) == 0)
    {
        spdlog::error("Failed to mount assets directory: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to mount assets directory");
    }
    spdlog::trace("Assets directory mounted.");

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

missiletoad::core::AssetManager::~AssetManager()
{
    spdlog::trace("AssetManager::~AssetManager() called.");
    PHYSFS_deinit();
    spdlog::trace("PhysFS deinitialized.");
    spdlog::trace("AssetManager::~AssetManager() finished.");
}
