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
    class PlayerSystem : public missiletoad::core::BaseSystem
    {
    public:
        PlayerSystem(missiletoad::core::Game *game);
        static void register_system(entt::meta_ctx &ctx);

        void on_update(float delta_time) override;
    };
} // namespace missiletoad::game
