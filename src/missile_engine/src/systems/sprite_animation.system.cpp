
#include "missile_engine/systems/sprite_animation.system.hpp"
#include "missile_engine/components/sprite.component.hpp"
#include "missile_engine/components/sprite_animation.component.hpp"

#include "missile_engine/components/disabled.component.hpp"
#include "missile_engine/game.hpp"

#include <algorithm>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <execution>

missileengine::SpriteAnimationSystem::SpriteAnimationSystem(missileengine::Game *game)
    : registry_(&game->active_scene().get_registry())
{
    registry_->on_construct<SpriteAnimationState>().connect<&SpriteAnimationSystem::on_sprite_animation_created>(this);
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
    auto view = registry_->view<SpriteComponent, SpriteAnimationState>(entt::exclude<DisabledComponent>);

    // Just update the animation
    std::for_each(std::execution::par_unseq, view.begin(), view.end(),
                  [&](auto entity)
                  {
                      auto &sprite    = view.get<SpriteComponent>(entity);
                      auto &animation = view.get<SpriteAnimationState>(entity);
                      animation.update(std::chrono::duration<float>(delta_time));
                      sprite.texture = animation.get_current_frame_texture();
                  });
}

void missileengine::SpriteAnimationSystem::on_sprite_animation_created(entt::registry &registry, entt::entity entity)
{
    auto &sprite = registry.get_or_emplace<SpriteComponent>(entity);
    unused(sprite);
    auto &animation = registry.get<SpriteAnimationState>(entity);

    animation.play(false);
    animation.loop(false);
}

missileengine::SpriteAnimationSystem::~SpriteAnimationSystem()
{
    registry_->on_construct<SpriteAnimationState>().disconnect<&SpriteAnimationSystem::on_sprite_animation_created>(
        this);
}
