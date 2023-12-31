#include "missile_toad/systems/turret.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/components/tag.component.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/bullet_utils.hpp"
#include "missile_toad/components/bullet.component.hpp"
#include "missile_toad/components/health.component.hpp"
#include "missile_toad/components/player.component.hpp"
#include "missile_toad/components/turret.component.hpp"
#include "missile_toad/systems/player.system.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <glm/glm.hpp>

missiletoad::TurretSystem::TurretSystem(missileengine::Game *game)
{
    using missileengine::EMouseButton;

    game->input_manager().add_action("shoot", EMouseButton::LEFT);
}

void missiletoad::TurretSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::TurretSystem>(ctx)
        .type("missiletoad::TurretSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}

void missiletoad::TurretSystem::on_start()
{

    spdlog::trace("missiletoad::TurretSystem::on_start() called.");
    auto &game  = missileengine::Game::get_instance();
    auto &scene = game.active_scene();

    // create turret
    auto       turret_texture = game.asset_manager().load<missileengine::Texture>("/assets/sprites/player/turret.png");
    const auto turret_transform_scale = glm::vec2{0.2F, 0.2F};
    scene.create_entity()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                constexpr auto turrret_position = glm::vec2{10.0F, 10.0F};
                transform.position              = turrret_position;
                transform.scale                 = {turret_transform_scale};
            })
        .with_component_using_function<missileengine::SpriteComponent>(
            [&](auto &sprite)
            {
                constexpr uint32_t turret_z_index = 101;
                sprite.z_index                    = turret_z_index;
            },
            std::move(turret_texture))
        .with_component_using_function<missileengine::Rigidbody2dComponent>([](auto &rigidbody)
                                                                            { rigidbody.set_static(false); })
        .with_component<missileengine::LineRendererComponent>()
        .with_component<missiletoad::TurretComponent>()
        .build();
}

void missiletoad::TurretSystem::on_fixed_update(float delta_time)
{
    unused(delta_time);

    auto &game           = missileengine::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto &input_manager  = game.input_manager();
    auto  mouse_input    = input_manager.get_mouse_position();

    auto view        = scene_entities.view<missiletoad::TurretComponent>();
    auto player_view = scene_entities.view<missiletoad::PlayerComponent>();
    auto camera_view = scene_entities.view<missileengine::Camera2dComponent>();

    for (auto player_entity : player_view)
    {
        for (auto camera_entity : camera_view)
        {
            for (auto entity : view)
            {
                auto &turret_transform = scene_entities.get<missileengine::TransformComponent>(entity);
                auto &line_renderer    = scene_entities.get<missileengine::LineRendererComponent>(entity);
                auto &camera           = scene_entities.get<missileengine::Camera2dComponent>(camera_entity);
                auto &player_transform = scene_entities.get<missileengine::TransformComponent>(player_entity);

                auto mouse_position = camera.get_screen_to_world(mouse_input);
                // the frog is only required to move the turret to the belt of the frog
                auto player_coordinates = player_transform.position;

                turret_transform.position.x = player_coordinates.x - 0.1f;
                turret_transform.position.y = player_coordinates.y - 0.45f;

                auto turret_coordinates = turret_transform.position;

                // Calculate the angle between the turret and the mouse
                float angle_radians =
                    atan2(mouse_position.y - turret_coordinates.y, mouse_position.x - turret_coordinates.x);
                float angle_degrees = glm::degrees(angle_radians);

                // Set the rotation of the turret based on the angle
                turret_transform.rotation = angle_degrees;

                line_renderer.start = {turret_coordinates.x, turret_coordinates.y};
                line_renderer.end   = {mouse_position.x, mouse_position.y};

                // DrawLine(mouse_position.x, mouse_position.y, turret_coordinates.x, turret_coordinates.y, RED);

                auto is_shooting = input_manager.get_action("shoot");

                if (is_shooting == missileengine::EActionState::PRESSED)
                {
                    create_bullet(turret_transform.position, mouse_position, 5.0F, 10.0F, false);
                }
            }
        }
    }
}
