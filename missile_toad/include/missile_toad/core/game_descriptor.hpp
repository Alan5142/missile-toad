#pragma once

#include "common.hpp"

namespace missiletoad::core
{
    struct PathFolder
    {
        std::string path;
        std::string mount_point;
    };

    struct GameDescriptor
    {
        std::string             name;
        std::vector<PathFolder> assets_folders;
    };

    std::optional<GameDescriptor> load_game_descriptor(std::string_view descriptor);
} // namespace missiletoad::core
