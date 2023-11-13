#include "missile_toad/systems/player.system.hpp"
#include "missile_toad/systems/turret.system.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/player.component.hpp"
#include "missile_toad/components/turret.component.hpp"

#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>

missiletoad::TurretSystem::TurretSystem(missileengine::Game *game)
{
 
}


void missiletoad::TurretSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::TurretSystem>(ctx)
            .type("missiletoad::TurretSystem"_hs)
            .base<missileengine::BaseSystem>()
            .ctor<missileengine::Game*>();
    // TODO: Add your register code here
}

void missiletoad::TurretSystem::on_update(float delta_time){
    unused(delta_time);

    auto &game           = missileengine::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto &input_manager  = game.input_manager();
    auto  mouse_input = input_manager.get_mouse_position();

    auto view = scene_entities.view<missiletoad::TurretComponent>();
    auto playerView = scene_entities.view<missiletoad::PlayerComponent>();
    auto cameraView = scene_entities.view<missileengine::Camera2dComponent>();

    for(auto playerEntity: playerView){
        for(auto cameraEntity: cameraView){
            for (auto entity : view)
            {
                auto &turret_transform = scene_entities.get<missileengine::TransformComponent>(entity);
                auto &line_renderer    = scene_entities.get<missileengine::LineRendererComponent>(entity);
                auto &camera           = scene_entities.get<missileengine::Camera2dComponent>(cameraEntity);
                auto &player_transform = scene_entities.get<missileengine::TransformComponent>(playerEntity);

                auto mouse_position = camera.get_screen_to_world(mouse_input);
                auto player_coordinates = player_transform.position;

                turret_transform.position.x = player_coordinates.x - 0.1f;
                turret_transform.position.y = player_coordinates.y - 0.25f;
                
                auto turret_coordinates = turret_transform.position;

                // Calculate the angle between the turret and the mouse
                float angleRadians = atan2(mouse_position.y - turret_coordinates.y, mouse_position.x - turret_coordinates.x);
                float angleDegrees = angleRadians * 180.0 / M_PI;

                spdlog::info(
                    "frog: {} {} turret: {} {} mouse: {} {} rotation: {}",  
                    player_coordinates.x,
                    player_coordinates.y,
                    turret_coordinates.x, 
                    turret_coordinates.y, 
                    mouse_position.x, 
                    mouse_position.y,
                    angleDegrees
                );

                // Set the rotation of the turret based on the angle
                turret_transform.rotation = angleDegrees;

                line_renderer.start = {turret_coordinates.x, turret_coordinates.y};
                line_renderer.end   = {mouse_position.x , mouse_position.y};

                DrawLine(mouse_position.x , mouse_position.y ,turret_coordinates.x, turret_coordinates.y, GREEN);

            }
        }

    }
}