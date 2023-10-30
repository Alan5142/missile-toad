#pragma once

#include "common.hpp"

namespace missileengine
{
    class Scene;
    class Game;

    /**
     * @brief The scene manager class manages the scenes in the game.
     * It is responsible for loading and unloading scenes.
     */
    class SceneManager
    {
    private:
        /**
         * @brief A pointer to the active scene.
         * nullptr if no scene is active.
         */
        std::unique_ptr<Scene> active_scene_;

        /**
         * @brief The name of the next scene to load.
         */
        std::optional<std::string> next_scene_;

        Game &game_;

    public:
        SceneManager(Game &game) noexcept;
        ~SceneManager() = default;

        SceneManager(const SceneManager &)            = delete;
        SceneManager(SceneManager &&)                 = delete;
        SceneManager &operator=(const SceneManager &) = delete;
        SceneManager &operator=(SceneManager &&)      = delete;

        /**
         * Performs an unloading of the next scene if one is queued.
         */
        void on_post_update();

        /**
         * Gets the active scene.
         * @return A pointer to the active scene. nullptr if no scene is active.
         */
        Scene *active_scene();

        /**
         * Loads a scene.
         * @param name
         */
        void load_scene(std::string_view name);
    };
} // namespace missileengine
