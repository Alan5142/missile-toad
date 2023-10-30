#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missileengine
{
    class Game;
}

namespace missiletoad
{
    /**
     * @brief System that encapsulates the Menu scene logic.
     * @details It will manage the Menu scene and will redirect to:
     * - The Hub scene if the player selects "Play New Game"
     * - Settings scene if the player selects "Settings"
     * - Exit the game if the player selects "Exit"
     */
    class MenuSystem : public missileengine::BaseSystem
    {
    public:
        MenuSystem(missileengine::Game *game);
        static void register_system(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
