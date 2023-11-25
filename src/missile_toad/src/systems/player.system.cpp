
#include "missile_toad/systems/player.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/player.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <missile_engine/components/circle_collider_2d.component.hpp>

void configure_player_axis(missileengine::Game *game)
{
    using missileengine::Action;
    using missileengine::EKey;

    const auto move_y_axis = missileengine::Axis{
        missileengine::AxisButton{EKey::S, EKey::W},
    };

    const auto move_y_gamepad_axis = missileengine::Axis{missileengine::GamepadAxisData{
        missileengine::EGamepadAxis::LEFT_Y,
        0,
    }};

    const auto move_x_axis = missileengine::Axis{
        missileengine::AxisButton{EKey::D, EKey::A},
    };

    const auto move_x_gamepad_axis = missileengine::Axis{missileengine::GamepadAxisData{
        missileengine::EGamepadAxis::LEFT_X,
        0,
    }};

    game->input_manager().add_axis("move_y", move_y_axis);
    game->input_manager().add_axis("move_y", move_y_gamepad_axis);

    game->input_manager().add_axis("move_x", move_x_axis);
    game->input_manager().add_axis("move_x", move_x_gamepad_axis);
}

missiletoad::PlayerSystem::PlayerSystem(missileengine::Game *game)
{
    using missileengine::Action;
    using missileengine::EKey;
    using missileengine::GamepadAxisData;

    configure_player_axis(game);
}

void missiletoad::PlayerSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::PlayerSystem>(ctx)
        .type("missiletoad::PlayerSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}

void missiletoad::PlayerSystem::on_start()
{
    spdlog::trace("game::PlayerSystem::on_start() called.");
    auto &game  = missileengine::Game::get_instance();
    auto &scene = game.active_scene();

    // Create player
    auto       player_texture = game.asset_manager().load<missileengine::Texture>("/assets/sprites/player/mt.png");
    const auto player_transform_scale = glm::vec2{1.0F, 1.0F};
    scene.create_entity()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                constexpr auto player_position = glm::vec2{10.0F, 5.0F};
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
        .with_component<missileengine::CircleCollider2dComponent>()
        .with_component<missiletoad::PlayerComponent>()
        .with_component_using_function<missileengine::SpriteAnimationComponent>(
            [&](auto &sprite_animation)
            {
                using namespace std::chrono_literals;
                auto idle_state = missileengine::SpriteAnimationState("idle");

                for (int i = 1; i <= 18; i++)
                {
                    auto idle_texture = game.asset_manager().load<missileengine::Texture>(
                        "/assets/sprites/player/idle/Toad" + std::to_string(i) + ".png");
                    idle_state.add_frame(idle_texture);
                }
                idle_state.set_timer(missileengine::TimerBuilder().with_interval(67ms).with_loop(true).build());
                idle_state.play(true); // Play the animation
                idle_state.loop(true); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("idle", idle_state);

                auto run_state = missileengine::SpriteAnimationState("run");

                for (int i = 1; i <= 13; i += 2)
                {
                    auto run_texture = game.asset_manager().load<missileengine::Texture>(
                        "/assets/sprites/player/move/Toad move" + std::to_string(i) + ".png");
                    run_state.add_frame(run_texture);
                }
                run_state.set_timer(missileengine::TimerBuilder().with_interval(20ms).with_loop(true).build());
                run_state.play(true); // Play the animation
                run_state.loop(true); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("run", run_state);

                sprite_animation.force_transition_to("idle");
            })
        .build();
}

void missiletoad::PlayerSystem::on_update(float delta_time)
{
    unused(delta_time);
    auto &game           = missileengine::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto &input_manager  = game.input_manager();

    auto view = scene_entities.view<missiletoad::PlayerComponent>();

    if (game.input_manager().is_key_pressed(missileengine::EKey::H))
    {
        game.set_debug_mode(!game.debug_mode());
    }

    for (auto entity : view)
    {
        auto &rigidbody = scene_entities.get<missileengine::Rigidbody2dComponent>(entity);
        auto &player    = scene_entities.get<missiletoad::PlayerComponent>(entity);
        auto &sprite    = scene_entities.get<missileengine::SpriteComponent>(entity);
        auto &animation = scene_entities.get<missileengine::SpriteAnimationComponent>(entity);

        auto move_x = input_manager.get_axis("move_x");
        auto move_y = input_manager.get_axis("move_y");

        if (move_x < 0)
        {
            sprite.flip_x = false;
        }
        else if (move_x > 0)
        {
            sprite.flip_x = true;
        }

        if (move_x != 0 || move_y != 0)
        {
            animation.force_transition_to("run");
        }
        else
        {
            animation.force_transition_to("idle");
        }

        rigidbody.set_linear_velocity({move_x * player.player_speed, move_y * player.player_speed});
    }
}
