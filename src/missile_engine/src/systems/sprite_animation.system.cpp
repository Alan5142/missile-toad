
#include "missile_engine/systems/sprite_animation.system.hpp"
#include "missile_engine/components/sprite.component.hpp"
#include "missile_engine/components/sprite_animation.component.hpp"

#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missileengine::SpriteAnimationSystem::SpriteAnimationSystem(missileengine::Game *game)
    : registry_(&game->active_scene().get_registry())
{
    registry_->on_construct<SpriteAnimationComponent>().connect<&SpriteAnimationSystem::on_sprite_animation_created>(
        this);
}

void missileengine::SpriteAnimationSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::SpriteAnimationSystem>(ctx)
        .type("missileengine::SpriteAnimationSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
}

void missileengine::SpriteAnimationSystem::on_update(float delta_time)
{
    auto view = registry_->view<SpriteComponent, SpriteAnimationComponent>();

    // Just update the animation
    for (auto entity : view)
    {
        auto &sprite    = view.get<SpriteComponent>(entity);
        auto &animation = view.get<SpriteAnimationComponent>(entity);
        animation.update(std::chrono::duration<float>(delta_time));
        sprite.texture = animation.get_current_frame_texture();
    }
}

void missileengine::SpriteAnimationSystem::on_sprite_animation_created(entt::registry &registry, entt::entity entity)
{
    auto &sprite = registry.get_or_emplace<SpriteComponent>(entity);
    unused(sprite);
    auto &animation = registry.get<SpriteAnimationComponent>(entity);

    animation.is_playing = false;
    animation.loop       = false;
}
missileengine::SpriteAnimationSystem::~SpriteAnimationSystem()
{
    registry_->on_construct<SpriteAnimationComponent>().disconnect<&SpriteAnimationSystem::on_sprite_animation_created>(
        this);
}
