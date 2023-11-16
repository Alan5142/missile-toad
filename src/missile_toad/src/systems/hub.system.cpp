
#include "missile_toad/systems/hub.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/components/circle_collider_2d.component.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/better_camera.component.hpp"
#include "missile_toad/components/player.component.hpp"
#include "missile_toad/components/turret.component.hpp"
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
    auto &game  = missileengine::Game::get_instance();
    auto &scene = game.active_scene();

    auto ldtk_project = game.asset_manager().load<ldtk::Project>("/assets/levels/testRoom.ldtk");

    // TODO: To be removed in the future.
    game.active_scene().segment_loader(*ldtk_project, "", 0, {{"Room", 0, true}, {"Ground", 0, false}});

    // Add camera system
    scene.add_system<missiletoad::CameraSystem>();

    // Create Experiment M
    constexpr auto enemy_sprite_length   = 8;
    const auto     enemy_transform_scale = glm::vec2{1.0F, 1.0F};
    scene.create_entity()
        .with_component_using_function<missileengine::SpriteAnimationComponent>(
            [&](auto &sprite_animation)
            {
                using namespace std::chrono_literals;
                auto run_state = missileengine::SpriteAnimationState("run");

                for (int i = 1; i <= enemy_sprite_length; i++)
                {
                    auto run_texture = game.asset_manager().load<missileengine::Texture>(
                        fmt::format("/assets/sprites/enemies/experiment_m/{}.png", i));
                    run_state.add_frame(run_texture);
                }
                run_state.set_timer(missileengine::TimerBuilder().with_interval(67ms).with_loop(true).build());
                run_state.play(true); // Play the animation
                run_state.loop(true); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("run", run_state);
            })
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                constexpr auto player_position = glm::vec2{10.0F, 10.0F};
                transform.position             = player_position;
                transform.scale                = {enemy_transform_scale};
            })
        .with_component_using_function<missileengine::SpriteComponent>(
            [&](auto &sprite)
            {
                constexpr uint32_t player_z_index = 100;
                sprite.z_index                    = player_z_index;
            },
            game.asset_manager().load<missileengine::Texture>("/assets/sprites/enemies/experiment_m/1.png"))
        .build();

    auto view = scene.view<missileengine::SpriteAnimationComponent>();

    for (auto entity : view)
    {
        auto &sprite_animation = view.get<missileengine::SpriteAnimationComponent>(entity);
        sprite_animation.force_transition_to("run"); // Waits for the current animation to finish
    }
}
