
#include "missile_toad/systems/hub.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_toad/components/better_camera.component.hpp"
#include "missile_toad/components/mecha_mosca.component.hpp"
#include "missile_toad/components/player.component.hpp"
#include "missile_toad/enemy_utils.hpp"
#include "missile_toad/systems/camera.system.hpp"
#include "missile_toad/systems/enemy.system.hpp"

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

void on_create_entity(const ldtk::Entity &entity)
{
    if (entity.getName() == "MechaMosca")
    {
        missiletoad::createExpM(static_cast<float>(entity.getPosition().x) / missileengine::PIXELS_PER_UNIT,
                                static_cast<float>(entity.getPosition().y) / missileengine::PIXELS_PER_UNIT);
    }
}

void missiletoad::HubSystem::on_start()
{
    spdlog::trace("game::HubSystem::on_start() called.");
    auto &game         = missileengine::Game::get_instance();
    auto &scene        = game.active_scene();
    auto  ldtk_project = game.asset_manager().load<ldtk::Project>("/assets/testRoom.ldtk");

    // TODO: To be removed in the future.
    game.active_scene().segment_loader(
        *ldtk_project, "", 0, {{"Room", 0, true}, {"Ground", 0, false}, {"Enemies", 0, false}}, on_create_entity);

    // Create player
    auto       player_texture         = game.asset_manager().load<missileengine::Texture>("/assets/mt.png");
    const auto player_transform_scale = glm::vec2{1.0F, 1.0F};
    scene.create_entity()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                constexpr auto player_position = glm::vec2{11.0F, 5.0F};
                transform.position             = player_position;
                transform.scale                = {player_transform_scale};
            })
        .with_component_using_function<missileengine::SpriteComponent>(
            [&](auto &sprite)
            {
                constexpr uint32_t player_z_index = 100;
                sprite.z_index                    = player_z_index;
                sprite.flip_x                     = true;
            },
            std::move(player_texture))
        .with_component_using_function<missileengine::Rigidbody2dComponent>([](auto &rigidbody)
                                                                            { rigidbody.set_static(false); })
        .with_component<missileengine::BoxCollider2dComponent>()
        .with_component<missiletoad::PlayerComponent>()
        .build();

    // Create camera
    const auto     camera_offset_x            = static_cast<float>(GetScreenWidth()) / 2.0F;
    const auto     camera_offset_y            = static_cast<float>(GetScreenHeight()) / 2.0F;
    constexpr auto camera_zoom                = 1.4F;
    constexpr auto better_camera_follow_speed = 3.5F;

    scene.create_entity()
        .with_component_using_function<missileengine::Camera2dComponent>(
            [&](auto &camera)
            {
                camera.set_zoom(camera_zoom);
                camera.set_offset({camera_offset_x, camera_offset_y});
                camera.set_is_main_camera(true);
            },
            glm::vec2{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())})
        .with_component<missileengine::TransformComponent>()
        .with_component<missiletoad::BetterCameraComponent>(0.0F, 0.0F, better_camera_follow_speed)
        .build();

    // Add camera system
    scene.add_system<missiletoad::CameraSystem>();

    scene.add_system<missiletoad::EnemySystem>();

    auto view = scene.view<missileengine::SpriteAnimationComponent>();

    for (auto entity : view)
    {
        auto &sprite_animation = view.get<missileengine::SpriteAnimationComponent>(entity);
        sprite_animation.force_transition_to("run"); // Waits for the current animation to finish
    }
}
