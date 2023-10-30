#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>

namespace missileengine
{
    class Game;

    class SpriteAnimationSystem : public missileengine::BaseSystem
    {
        entt::registry *registry_;

    public:
        SpriteAnimationSystem(missileengine::Game *game);
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
} // namespace missileengine
