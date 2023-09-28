
#include "missile_toad/core/systems/audio.system.hpp"
#include "missile_toad/core/components/audio.component.hpp"
#include "missile_toad/core/game.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::core::AudioSystem::AudioSystem(missiletoad::core::Game *game)
    : registry_(&game->active_scene().get_registry())
{
}

void missiletoad::core::AudioSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::AudioSystem>(ctx)
        .type("missiletoad::core::AudioSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<missiletoad::core::Game *>();
    // TODO: Add your register code here
}

void missiletoad::core::AudioSystem::on_update(float delta_time)
{
    auto view = registry_->view<core::AudioComponent>();

    unused(delta_time);

    for (auto entity : view)
    {
        auto &audio = view.get<core::AudioComponent>(entity);
        audio.sound->get_music().Update();
    }
}

missiletoad::core::AudioSystem::~AudioSystem()
{
}
