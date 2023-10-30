#pragma once

#include "common.hpp"

namespace missileengine
{
    /**
     * A descriptor for a scene.
     */
    struct SceneDescriptor
    {
        /**
         * The name of the scene.
         */
        std::string name;
        /**
         * The systems of the scene.
         */
        std::vector<std::string> systems;
    };

    /**
     * Loads a descriptor for a scene.
     * @param path The path to the scene descriptor.
     * @return The scene descriptor.
     */
    [[nodiscard]] std::optional<SceneDescriptor> load_scene_descriptor(std::string_view path);
} // namespace missileengine
