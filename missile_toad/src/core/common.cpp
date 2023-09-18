/// @file missile_toad/src/core/common.cpp

#include "missile_toad/core/common.hpp"
#include <physfs.h>

// NOLINTNEXTLINE(*-avoid-c-arrays)
std::optional<std::pair<std::unique_ptr<uint8_t[]>, size_t>> missiletoad::core::load_file(std::string_view name)
{
    spdlog::trace("load_file() called. with file: {}", name);
    // Load texture from memory using PhysFS
    PHYSFS_File *file = PHYSFS_openRead(name.data());

    // Check if the file exists
    if (file == nullptr)
    {
        spdlog::error("Failed to open file: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        return {};
    }

    // Get the size of the file
    PHYSFS_sint64 size = PHYSFS_fileLength(file);

    // Allocate memory for the file
    auto data = std::make_unique<uint8_t[]>(size); // NOLINT(*-avoid-c-arrays)

    // Read the file into memory
    if (PHYSFS_readBytes(file, data.get(), size) == -1)
    {
        spdlog::error("Failed to read file: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        return {};
    }

    // Close the file
    if (PHYSFS_close(file) == 0)
    {
        spdlog::error("Failed to close file: {}", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        return {};
    }
    return {{std::move(data), static_cast<size_t>(size)}};
}
