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
    class BulletSystem : public missileengine::BaseSystem
    {
    public:
        BulletSystem(missileengine::Game *game);
        static void register_system(entt::meta_ctx &ctx);

        const int MAX_BULLTS = 200;
        // std::vector<>

        void on_start() override;
        void on_update(float delta_time) override;
    };
} // namespace missiletoad
