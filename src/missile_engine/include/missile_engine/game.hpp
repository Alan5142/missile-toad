#pragma once

#include "missile_engine/common.hpp"
#include "missile_engine/scene.hpp"
#include "raylib-nuklear.h"

#include <entt/meta/factory.hpp>
#include <raylib-cpp.hpp>
#include <vector>

namespace missileengine
{
    class BaseSystem;
    class AssetManager;
    class SceneManager;
    struct GameDescriptor;
    class InputManager;

    /**
     * A class that represents the game.
     * It includes the main loop and the game state.
     *
     * This class serves as a higher level abstraction to all the other classes
     * in the game, such as the renderer, the input manager, the physics engine, etc.
     * It contains all of the game's state, and it is responsible for updating it
     * and rendering it.
     */
    class Game
    {
        entt::meta_ctx                                      systems_meta_ctx_;
        entt::meta_ctx                                      components_meta_ctx_;
        std::vector<std::unique_ptr<BaseSystem>>            components_;
        std::unique_ptr<AssetManager>                       asset_manager_;
        std::unique_ptr<SceneManager>                       scene_manager_;
        std::unique_ptr<InputManager>                       input_manager_;
        std::unique_ptr<nk_context, void (*)(nk_context *)> nuklear_context_;
        raylib::Window                                      window_;
        bool                                                debug_mode_{};

    public:
        /**
         * The constructor of the game. It initializes all of the systems and managers in the game.
         *
         * Argv and argc are used to select some game options, such as the debug mode. etc.
         * @param argc argc passed to main.
         * @param argv argv passed to main.
         */
        Game(std::vector<std::string_view> &&arguments, const GameDescriptor &game_descriptor);

        /**
         * Returns the instance of the game.
         * @return The instance of the game.
         */
        static Game &get_instance() noexcept;

        ~Game() noexcept;

        Game(const Game &)            = delete;
        Game(Game &&)                 = delete;
        Game &operator=(const Game &) = delete;
        Game &operator=(Game &&)      = delete;

        /**
         * The game loop of the game. It runs the game.
         * @param argc main's argc
         * @param argv main's argv
         */
        void run() noexcept;

        /**
         * Closes the game.
         */
        void close() noexcept;

        /**
         * Returns the asset manager of the game.
         * @return The asset manager of the game.
         */
        [[nodiscard]] missileengine::AssetManager &asset_manager() noexcept;

        [[nodiscard]] missileengine::SceneManager &scene_manager() noexcept;

        [[nodiscard]] missileengine::InputManager &input_manager() noexcept;

        [[nodiscard]] missileengine::Scene &active_scene() noexcept;

        [[nodiscard]] entt::meta_ctx &systems_meta_ctx() noexcept
        {
            return systems_meta_ctx_;
        }

        [[nodiscard]] entt::meta_ctx &components_meta_ctx() noexcept
        {
            return components_meta_ctx_;
        }

    private:
        /**
         * The main loop of the game. It updates all of the systems and managers in the game.
         * @param delta_time The time in seconds since the last frame.
         */
        void update(float delta_time) noexcept;

        /**
         * The fixed update loop of the game. It updates all of the systems and managers in the game.
         * This is called at a fixed rate (UPDATE_RATE). This is useful for physics.
         * @param delta_time The time in seconds since the last frame. (Should be equal to UPDATE_RATE)
         */
        void fixed_update(float delta_time) noexcept;

        /**
         * The render loop of the game. It renders all of the systems and managers in the game.
         * This is called once per frame, this means that it is not called at a fixed rate.
         * So, this is not a place to put game logic.
         */
        void render() noexcept;

        /**
         *
         */
        void debug_gui() noexcept;
    };
} // namespace missileengine
