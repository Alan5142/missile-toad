#pragma once

#include "common.hpp"

namespace missileengine
{
    /**
     * Represents a folder, used to specify the mount points for the VFS.
     */
    struct PathFolder
    {
        /**
         * @brief The path to the folder in the filesystem.
         */
        std::string path;

        /**
         * Where to mount the folder in the VFS.
         */
        std::string mount_point;
    };

    /**
     * @brief The game descriptor. It includes the name of the game, the default scene and the assets folders.
     */
    struct GameDescriptor
    {
        /**
         * @brief The name of the game.
         */
        std::string name;

        /**
         * @brief The default scene to load.
         */
        std::string default_scene;

        /**
         * @brief The assets folders.
         */
        std::vector<PathFolder> assets_folders;
    };

    /**
     * @brief Loads a game descriptor from a string.
     * @param descriptor The descriptor to load.
     * @return The loaded game descriptor.
     */
    std::optional<GameDescriptor> load_game_descriptor(std::string_view descriptor);
} // namespace missileengine
