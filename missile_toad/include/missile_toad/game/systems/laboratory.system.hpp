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
     * @brief System that encapsulates the Laboratory scene logic.
     * @details It will manage the Laboratory scene, which is the first playable level
     *
     */
    class LaboratorySystem : public missiletoad::core::BaseSystem
    {
    public:
        LaboratorySystem(missiletoad::core::Game *game);
        static void register_system(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::game
