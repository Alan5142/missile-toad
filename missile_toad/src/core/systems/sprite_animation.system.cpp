
#include "missile_toad/core/systems/sprite_animation.system.hpp"
#include "missile_toad/core/components/sprite.component.hpp"
#include "missile_toad/core/components/sprite_animation.component.hpp"

#include "missile_toad/core/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::core::SpriteAnimationSystem::SpriteAnimationSystem(missiletoad::core::Game *game)
    : registry_(&game->active_scene().get_registry())
{
    registry_->on_construct<core::SpriteAnimationComponent>()
        .connect<&SpriteAnimationSystem::on_sprite_animation_created>(this);
}

void missiletoad::core::SpriteAnimationSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::SpriteAnimationSystem>(ctx)
        .type("missiletoad::core::SpriteAnimationSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<missiletoad::core::Game *>();
}

void missiletoad::core::SpriteAnimationSystem::on_update(float delta_time)
{
    auto view = registry_->view<core::SpriteComponent, core::SpriteAnimationComponent>();

    // Just update the animation
    for (auto entity : view)
    {
        auto &sprite    = view.get<core::SpriteComponent>(entity);
        auto &animation = view.get<core::SpriteAnimationComponent>(entity);
        animation.update(std::chrono::duration<float>(delta_time));
        sprite.texture = animation.get_current_frame_texture();
    }
}

void missiletoad::core::SpriteAnimationSystem::on_sprite_animation_created(entt::registry &registry,
                                                                           entt::entity    entity)
{
    auto &sprite = registry.get_or_emplace<core::SpriteComponent>(entity);
    unused(sprite);
    auto &animation = registry.get<core::SpriteAnimationComponent>(entity);

    animation.is_playing = false;
    animation.loop       = false;
}
missiletoad::core::SpriteAnimationSystem::~SpriteAnimationSystem()
{
    registry_->on_construct<core::SpriteAnimationComponent>()
        .disconnect<&SpriteAnimationSystem::on_sprite_animation_created>(this);
}
