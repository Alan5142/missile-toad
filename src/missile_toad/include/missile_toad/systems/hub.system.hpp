#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_toad/components/better_camera.component.hpp"

#include <entt/meta/meta.hpp>

namespace missileengine
{
    class Game;
}

namespace missiletoad
{
    /**
     * @brief System that encapsulates the Hub scene logic.
     * @details It will manage the Hub scene, which is the scene that the player
     * will be in when they are not in a level.
     */
    class HubSystem : public missileengine::BaseSystem
    {
    public:
        HubSystem(missileengine::Game *game);
        static void register_system(entt::meta_ctx &ctx);

        void on_start() override;

        void on_update(float delta_time) override;
    };
} // namespace missiletoad
