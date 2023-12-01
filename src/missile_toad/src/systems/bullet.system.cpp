
#include "missile_toad/systems/bullet.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/components/tag.component.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/bullet.component.hpp"
#include "missile_toad/components/health.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <glm/glm.hpp>

missiletoad::BulletSystem::BulletSystem(missileengine::Game *game)
{
    unused(game);
}

void missiletoad::BulletSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::BulletSystem>(ctx)
        .type("missiletoad::BulletSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}

void missiletoad::BulletSystem::on_start()
{
    spdlog::trace("missiletoad::BulletSystem::on_start() called.");
}

void missiletoad::BulletSystem::on_update(float delta_time)
{
    unused(delta_time);
    spdlog::trace("missiletoad::BulletSystem::on_update() called.");
    auto &game           = missileengine::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();

    auto view = scene_entities.view<missiletoad::BulletComponent>();

    for (auto entity : view)
    {
        auto &rigidbody = scene_entities.get<missileengine::Rigidbody2dComponent>(entity);
        auto &bullet    = scene_entities.get<missiletoad::BulletComponent>(entity);

        rigidbody.set_linear_velocity(bullet.direction * bullet.velocity);
    }
}
