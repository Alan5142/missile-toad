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
     * @brief System that encapsulates the Laboratory scene logic.
     * @details It will manage the Laboratory scene, which is the first playable level
     *
     */
    class LaboratorySystem : public missileengine::BaseSystem
    {
    public:
        LaboratorySystem(missileengine::Game *game);
        static void register_system(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
