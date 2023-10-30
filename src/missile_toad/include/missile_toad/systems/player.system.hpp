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
    class PlayerSystem : public missileengine::BaseSystem
    {
    public:
        PlayerSystem(missileengine::Game *game);
        static void register_system(entt::meta_ctx &ctx);

        void on_update(float delta_time) override;
    };
} // namespace missiletoad
