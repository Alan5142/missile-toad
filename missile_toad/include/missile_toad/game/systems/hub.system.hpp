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
     * @brief System that encapsulates the Hub scene logic.
     * @details It will manage the Hub scene, which is the scene that the player
     * will be in when they are not in a level.
     */
    class HubSystem : public missiletoad::core::BaseSystem
    {
    public:
        HubSystem(missiletoad::core::Game *game);
        static void register_system(entt::meta_ctx &ctx);

        void on_start() override;
    };
} // namespace missiletoad::game
