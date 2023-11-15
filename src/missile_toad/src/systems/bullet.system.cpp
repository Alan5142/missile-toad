
#include "missile_toad/systems/bullet.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/bullet.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void configure_shooting_keys(missileengine::Game *game)
{
    using missileengine::Action;
    using missileengine::EMouseButton;

    const auto shoot = missileengine::Axis{
        missileengine::AxisButton{EMouseButton::LEFT},
    };

    game->input_manager().add_axis("shoot", shoot);
}

missiletoad::BulletSystem::BulletSystem(missileengine::Game *game)
{
    using missileengine::Action;
    using missileengine::EMouseButton;

    configure_shooting_keys(game);
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
    // auto &game         = missileengine::Game::get_instance();
    // auto &scene        = game.active_scene();

    // auto bullet_texture = game.asset_manager().load<missileengine::Texture>("/assets/sprites/bullets/bala.png");
    // const auto bullet_transform_scale = glm::vec2{0.2F, 0.2F};
}

void missiletoad::BulletSystem::on_update(float delta_time)
{
    unused(delta_time);
    spdlog::trace("missiletoad::BulletSystem::on_update() called.");
    auto &game           = missileengine::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto &input_manager  = game.input_manager();

    auto view = scene_entities.view<missiletoad::BulletComponent>();

    for (auto entity : view)
    {
        auto is_shooting = input_manager.get_axis("shoot");

        spdlog::trace("Is shooting {}", is_shooting);
    }
}
