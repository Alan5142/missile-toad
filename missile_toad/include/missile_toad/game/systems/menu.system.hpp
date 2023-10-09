#pragma once
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad::core
{
    class Game;
}

namespace missiletoad::game
{
    /**
     * @brief System that encapsulates the Menu scene logic.
     * @details It will manage the Menu scene and will redirect to:
     * - The Hub scene if the player selects "Play New Game"
     * - Settings scene if the player selects "Settings"
     * - Exit the game if the player selects "Exit"
     */
    class MenuSystem : public missiletoad::core::BaseSystem
    {
    public:
        MenuSystem(missiletoad::core::Game *game);
        static void register_system(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::game
