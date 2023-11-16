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
    class HealthSystem : public missileengine::BaseSystem
    {
    public:
        HealthSystem(missileengine::Game *game);
        static void register_system(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
