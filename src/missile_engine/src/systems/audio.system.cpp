
#include "missile_engine/systems/audio.system.hpp"
#include "missile_engine/components/audio.component.hpp"
#include "missile_engine/components/disabled.component.hpp"
#include "missile_engine/game.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missileengine::AudioSystem::AudioSystem(missileengine::Game *game) : registry_(&game->active_scene().get_registry())
{
}

void missileengine::AudioSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::AudioSystem>(ctx)
        .type("missileengine::AudioSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}

void missileengine::AudioSystem::on_update(float delta_time)
{
    auto view = registry_->view<AudioComponent>(entt::exclude<missileengine::DisabledComponent>);

    unused(delta_time);

    for (auto entity : view)
    {
        auto &audio = view.get<AudioComponent>(entity);
        audio.sound->get_music().Update();
    }
}

missileengine::AudioSystem::~AudioSystem() = default;
