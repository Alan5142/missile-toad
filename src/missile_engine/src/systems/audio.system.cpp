
#include "missile_engine/systems/audio.system.hpp"
#include "missile_engine/components/audio.component.hpp"
#include "missile_engine/game.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missilengine::AudioSystem::AudioSystem(missilengine::Game *game) : registry_(&game->active_scene().get_registry())
{
}

void missilengine::AudioSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missilengine::AudioSystem>(ctx)
        .type("missilengine::AudioSystem"_hs)
        .base<missilengine::BaseSystem>()
        .ctor<missilengine::Game *>();
    // TODO: Add your register code here
}

void missilengine::AudioSystem::on_update(float delta_time)
{
    auto view = registry_->view<AudioComponent>();

    unused(delta_time);

    for (auto entity : view)
    {
        auto &audio = view.get<AudioComponent>(entity);
        audio.sound->get_music().Update();
    }
}

missilengine::AudioSystem::~AudioSystem() = default;
