
#include "missile_toad/systems/hub.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_toad/components/better_camera.component.hpp"
#include "missile_toad/components/player.component.hpp"
#include "missile_toad/systems/camera.system.hpp"

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
    auto       player_texture         = game.asset_manager().load<missileengine::Texture>("/assets/mt.png");
    const auto player_transform_scale = glm::vec2{1.0F, 1.0F};
    scene.create_entity()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                constexpr auto player_position = glm::vec2{10.0F, 10.0F};
                transform.position             = player_position;
                transform.scale                = {player_transform_scale};
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

    // wrong way to add sprites
    auto run_texture_1 = asset_manager.load<missileengine::Texture>("run_1.png");
    auto run_texture_2 = asset_manager.load<missileengine::Texture>("run_2.png");
    auto run_texture_3 = asset_manager.load<missileengine::Texture>("run_3.png");

    auto idle_texture_1 = asset_manager.load<missileengine::Texture>("idle_1.png");
    auto idle_texture_2 = asset_manager.load<missileengine::Texture>("idle_2.png");
    auto idle_texture_3 = asset_manager.load<missileengine::Texture>("idle_3.png");

    // better way using for loop
    for (int i = 1; i <= 3; i++)
    {
        auto run_texture  = asset_manager.load<missileengine::Texture>("run_" + std::to_string(i) + ".png");
        auto idle_texture = asset_manager.load<missileengine::Texture>("idle_" + std::to_string(i) + ".png");
    }

    scene.create_entity()
        .with_component_using_function<missileengine::SpriteAnimationComponent>(
            [&](auto &sprite_animation)
            {
                auto run_state = missileengine::SpriteAnimationState("run");
                for (int i = 1; i <= 3; i++)
                {
                    auto run_texture =
                        scene.asset_manager.load<missileengine::Texture>("run_" + std::to_string(i) + ".png");
                    run_state.add_frame(run_texture);
                }
                run_state.play(true); // Play the animation
                run_state.loop(true); // Loop the animation until a transition is triggered or the animation is stopped

                auto idle_to_run_transition = missileengine::SpriteAnimationTransition::create_manual();
                idle_state.add_transition("run", idle_to_run_transition); // Must match the state name

                sprite_animation.add_state(run_state);
            })
        .build();

    auto view = scene.view<missileengine::SpriteAnimationComponent>();

    for (auto entity : view)
    {
        auto &sprite_animation = view.get<missileengine::SpriteAnimationComponent>();
        sprite_animation.transition_to("run"); // Waits for the current animation to finish
        sprite_animation.force_transition_to(
            "run"); // Force the transition, the current animation is stopped and the new one is played
    }
}
