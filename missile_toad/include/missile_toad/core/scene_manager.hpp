#pragma once

#include "common.hpp"

namespace missiletoad::core
{
    class Scene;

    class SceneManager
    {
    public:
        SceneManager()  = default;
        ~SceneManager() = default;

        SceneManager(const SceneManager &)            = delete;
        SceneManager(SceneManager &&)                 = delete;
        SceneManager &operator=(const SceneManager &) = delete;
        SceneManager &operator=(SceneManager &&)      = delete;

        const Scene &get_active_scene() const;
        Scene       &get_active_scene();
        void         set_active_scene(uint64_t scene_hash);
        void         load_scene_metadata_from_directory(std::string_view directory_path);
    };
} // namespace missiletoad::core
