#pragma once
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/common.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>

namespace missiletoad::core
{
    class Game;

    class SpriteAnimationSystem : public missiletoad::core::BaseSystem
    {
        entt::registry *registry_;

    public:
        SpriteAnimationSystem(missiletoad::core::Game *game);
        SpriteAnimationSystem(const SpriteAnimationSystem &) = delete;
        SpriteAnimationSystem(SpriteAnimationSystem &&)      = delete;

        SpriteAnimationSystem &operator=(const SpriteAnimationSystem &) = delete;
        SpriteAnimationSystem &operator=(SpriteAnimationSystem &&)      = delete;

        ~SpriteAnimationSystem() override;
        static void register_system(entt::meta_ctx &ctx);

        void on_update(float delta_time) override;

    private:
        /**
         * Called when a sprite animation is created.
         * @param registry registry
         * @param entity entity
         */
        void on_sprite_animation_created(entt::registry &registry, entt::entity entity);
    };
} // namespace missiletoad::core
