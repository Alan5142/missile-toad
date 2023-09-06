#pragma once

#include "missile_toad/common.hpp"
#include "raylib-nuklear.h"

#include <entt/meta/factory.hpp>
#include <vector>

namespace missiletoad
{
    class BaseSystem;

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
        int                                                 argc;
        char                                              **argv;
        std::unique_ptr<nk_context, void (*)(nk_context *)> nuklear_context;
        std::vector<std::unique_ptr<BaseSystem>>            components;
        entt::meta_ctx                                      meta_context;

    public:
        /**
         * The constructor of the game. It initializes all of the systems and managers in the game.
         *
         * Argv and argc are used to select some game options, such as the debug mode. etc.
         * @param argc argc passed to main.
         * @param argv argv passed to main.
         */
        Game(int argc, char **argv) noexcept;
        ~Game() noexcept;

        Game(const Game &)            = delete;
        Game(Game &&)                 = delete;
        Game &operator=(const Game &) = delete;
        Game &operator=(Game &&)      = delete;

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
    };
} // namespace missiletoad