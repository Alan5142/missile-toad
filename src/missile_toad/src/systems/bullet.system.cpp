
#include "missile_toad/systems/bullet.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/bullet.component.hpp"
#include "missile_engine/core_components.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

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
    // auto &game         = missileengine::Game::get_instance();
    // auto &scene        = game.active_scene();


    // // Create bullet
    // auto bullet_texture = game.asset_manager().load<missileengine::Texture>("/assets/sprites/bullets/bala.png");
    // const auto bullet_transform_scale = glm::vec2{0.2F, 0.2F};

    // scene.create_entity()
    //     .with_component_using_function<missileengine::TransformComponent>(
    //         [&](auto &transform)
    //         {
    //             constexpr auto bullet_position = glm::vec2{10.0F, 10.0F};
    //             transform.position             = bullet_position;
    //             transform.scale                = {bullet_transform_scale};
    //         })
    //     .with_component_using_function<missileengine::SpriteComponent>(
    //         [&](auto &sprite)
    //         {
    //             constexpr uint32_t bullet_z_index = 101;
    //             sprite.z_index                    = bullet_z_index;
    //         },
    //         std::move(bullet_texture))
    //     .with_component_using_function<missileengine::Rigidbody2dComponent>([](auto &rigidbody)
    //                                                                         { rigidbody.set_static(false); })
    //     .with_component<missileengine::BoxCollider2dComponent>()
    //     .with_component<missiletoad::BulletComponent>()
    //     .build();
}

void move_bullet(){

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
        auto &transform = scene_entities.get<missileengine::TransformComponent>(entity);
        auto &bullet = scene_entities.get<missiletoad::BulletComponent>(entity);

        rigidbody.set_linear_velocity(bullet.direction * bullet.velocity);

    }
}
