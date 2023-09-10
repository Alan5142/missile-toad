#include "missile_toad/core/asset_manager.hpp"
#include "physfs.h"

static constexpr std::string_view NX_ASSETS_PATH = "romfs:/assets";

static constexpr std::string_view PC_ASSETS_PATH = "missiletoad.assets";

missiletoad::core::AssetManager::AssetManager()
{
    // Init PhysFS
    if (PHYSFS_init(nullptr) == 0)
    {
        spdlog::error("Failed to init PhysFS: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to init PhysFS");
    }

    // Mount the base directory
#if defined(PLATFORM_NX)
    if (PHYSFS_mount(NX_ASSETS_PATH.data(), nullptr, 0) == 0)
    {
        spdlog::error("Failed to mount assets directory: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to mount assets directory");
    }
#else
    if (PHYSFS_mount(PC_ASSETS_PATH.data(), nullptr, 0) == 0)
    {
        spdlog::error("Failed to mount assets directory: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        throw std::runtime_error("Failed to mount assets directory");
    }
#endif
}

missiletoad::core::AssetManager::~AssetManager()
{
    PHYSFS_deinit();
}
