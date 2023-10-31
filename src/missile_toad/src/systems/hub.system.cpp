
#include "missile_toad/systems/hub.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_toad/components/better_camera.component.hpp"
#include "missile_toad/components/player.component.hpp"

#include <cmath>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::HubSystem::HubSystem(missileengine::Game *game)
{
    // TODO: Add your constructor code here
    spdlog::trace("game::HubSystem() called.");

    unused(game);
    spdlog::trace("game::HubSystem() called.");
}

void missiletoad::HubSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::HubSystem>(ctx)
        .type("missiletoad::HubSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}

void missiletoad::HubSystem::on_start()
{
    spdlog::trace("game::HubSystem::on_start() called.");
    auto &game         = missileengine::Game::get_instance();
    auto &scene        = game.active_scene();
    auto  ldtk_project = game.asset_manager().load<ldtk::Project>("/assets/testRoom.ldtk");

    // TODO: To be removed in the future.
    game.active_scene().segment_loader(*ldtk_project, "", 0, {{"Room", 0, true}, {"Ground", 0, false}});

    // Create player
    auto player_texture = game.asset_manager().load<missileengine::Texture>("/assets/mt.png");
    scene.create_entity()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                constexpr auto player_position = glm::vec2{10.0F, 10.0F};
                transform.position             = player_position;
            })
        .with_component_using_function<missileengine::SpriteComponent>(
            [&](auto &sprite)
            {
                constexpr uint32_t player_z_index = 100;
                sprite.z_index                    = player_z_index;
            },
            std::move(player_texture))
        .with_component_using_function<missileengine::Rigidbody2dComponent>([](auto &rigidbody)
                                                                            { rigidbody.set_static(false); })
        .with_component<missileengine::BoxCollider2dComponent>()
        .with_component<missiletoad::PlayerComponent>()
        .build();

    // Create camera
    scene.create_entity()
        .with_component_using_function<missileengine::Camera2dComponent>(
            [](auto &camera)
            {
                camera.set_zoom(1.4F);
                camera.set_offset({GetScreenWidth() / 2.0F, GetScreenHeight() / 2.0F});
            })
        .with_component<missileengine::TransformComponent>()
        .with_component<missiletoad::BetterCameraComponent>(0.0F, 0.0F, 3.5F)
        .build();
}

void missiletoad::HubSystem::on_update(float delta_time)
{
    auto                              &game             = missileengine::Game::get_instance();
    auto                              &scene            = game.active_scene();
    missileengine::TransformComponent *player_transform = nullptr;

    unused(delta_time);

    auto player_view = scene.view<missiletoad::PlayerComponent, missileengine::TransformComponent>();
    for (auto entity : player_view)
    {
        player_transform = &player_view.get<missileengine::TransformComponent>(entity);
    }

    auto view = scene.view<missileengine::Camera2dComponent, missiletoad::BetterCameraComponent,
                           missileengine::TransformComponent>();
    for (auto entity : view)
    {
        auto &transform_component     = view.get<missileengine::TransformComponent>(entity);
        auto &better_camera_component = view.get<missiletoad::BetterCameraComponent>(entity);

        float xTarget = player_transform->position.x + better_camera_component.x_offset;
        float yTarget = player_transform->position.y + better_camera_component.y_offset;

        float xNew =
            std::lerp(transform_component.position.x, xTarget, delta_time * (better_camera_component.follow_speed));
        float yNew =
            std::lerp(transform_component.position.y, yTarget, delta_time * (better_camera_component.follow_speed));

        spdlog::info("xNew: {}, yNew: {}, xTarget{}, yTarget{}", xNew, yNew, xTarget, yTarget);

        transform_component.position.x = xNew;
        transform_component.position.y = yNew;
    }
}
