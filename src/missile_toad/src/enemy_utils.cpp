#include "missile_toad/enemy_utils.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_toad/components/caracool.component.hpp"
#include "missile_toad/components/experimento_m.component.hpp"
#include "missile_toad/components/health.component.hpp"
#include "missile_toad/components/king_mecha_rat.component.hpp"
#include "missile_toad/components/mecha_mosca.component.hpp"

void missiletoad::createExpM(float pos_x, float pos_y)
{
    auto          &game                   = missileengine::Game::get_instance();
    auto          &scene                  = game.active_scene();
    const auto     player_transform_scale = glm::vec2{1.0F, 1.0F};
    constexpr auto enemy_sprite_length    = 8;
    scene.create_entity()
        .with_component_using_function<missileengine::SpriteAnimationComponent>(
            [&](auto &sprite_animation)
            {
                using namespace std::chrono_literals;
                auto run_state = missileengine::SpriteAnimationState("run");

                for (int i = 1; i <= enemy_sprite_length; i++)
                {
                    auto run_texture = game.asset_manager().load<missileengine::Texture>(
                        "/assets/sprites/enemies/experiment_m/move/" + std::to_string(i) + ".png");
                    run_state.add_frame(run_texture);
                }
                run_state.set_timer(missileengine::TimerBuilder().with_interval(76ms).with_loop(true).build());
                run_state.play(true); // Play the animation
                run_state.loop(true); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("run", run_state);

                auto death_state = missileengine::SpriteAnimationState("death");

                for (int i = 1; i <= 8; i++)
                {
                    auto death_texture = game.asset_manager().load<missileengine::Texture>(
                        "/assets/sprites/enemies/experiment_m/move/" + std::to_string(i) + ".png");
                    death_state.add_frame(death_texture);
                }

                death_state.set_timer(missileengine::TimerBuilder().with_interval(12ms).with_loop(false).build());
                death_state.play(true); // Play the animation
                death_state.loop(
                    false); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("death", death_state);

                auto idle_state = missileengine::SpriteAnimationState("idle");

                for (int i = 1; i <= 8; i++)
                {
                    auto death_texture = game.asset_manager().load<missileengine::Texture>(
                        "/assets/sprites/enemies/experiment_m/idle/" + std::to_string(i) + ".png");
                    idle_state.add_frame(death_texture);
                }

                idle_state.set_timer(missileengine::TimerBuilder().with_interval(125ms).with_loop(false).build());
                idle_state.play(true); // Play the animation
                idle_state.loop(
                    false); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("idle", idle_state);

                auto attack_state = missileengine::SpriteAnimationState("attack");

                for (int i = 1; i <= 8; i++)
                {
                    auto death_texture = game.asset_manager().load<missileengine::Texture>(
                        "/assets/sprites/enemies/experiment_m/attack/a" + std::to_string(i) + ".png");
                    attack_state.add_frame(death_texture);
                }

                attack_state.set_timer(missileengine::TimerBuilder().with_interval(125ms).with_loop(false).build());
                attack_state.play(true); // Play the animation
                attack_state.loop(
                    false); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("attack", attack_state);

                sprite_animation.force_transition_to("run");
            })
        .with_component_using_function<missileengine::Rigidbody2dComponent>([](auto &rigidbody)
                                                                            { rigidbody.set_static(false); })
        .with_component<missileengine::BoxCollider2dComponent>()
        .with_component<missiletoad::ExperimentoMComponent>()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                transform.position = glm::vec2{pos_x, pos_y};
                transform.scale    = {player_transform_scale};
            })
        .with_component_using_function<missileengine::SpriteComponent>(
            [&](auto &sprite)
            {
                constexpr uint32_t player_z_index = 100;
                sprite.z_index                    = player_z_index;
            },
            game.asset_manager().load<missileengine::Texture>("/assets/sprites/enemies/experiment_m/move/1.png"))
        .with_component<missiletoad::HealthComponent>()
        .with_tag("Enemy")
        .build();
}

void missiletoad::createMechaMosquito(float pos_x, float pos_y)
{
    auto          &game                   = missileengine::Game::get_instance();
    auto          &scene                  = game.active_scene();
    const auto     player_transform_scale = glm::vec2{1.0F, 1.0F};
    constexpr auto enemy_sprite_length    = 16;
    scene.create_entity()
        .with_component_using_function<missileengine::SpriteAnimationComponent>(
            [&](auto &sprite_animation)
            {
                using namespace std::chrono_literals;
                auto run_state = missileengine::SpriteAnimationState("run");

                for (int i = 1; i <= enemy_sprite_length; i++)
                {
                    auto run_texture = game.asset_manager().load<missileengine::Texture>(
                        "/assets/sprites/enemies/mecha_mosquito/move_idle/mecha" + std::to_string(i) + ".png");
                    run_state.add_frame(run_texture);
                }
                run_state.set_timer(missileengine::TimerBuilder().with_interval(10ms).with_loop(true).build());
                run_state.play(true); // Play the animation
                run_state.loop(true); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("run", run_state);

                auto death_state = missileengine::SpriteAnimationState("death");

                for (int i = 1; i <= 8; i++)
                {
                    auto death_texture = game.asset_manager().load<missileengine::Texture>(
                        "/assets/sprites/enemies/mecha_mosquito/death/death" + std::to_string(i) + ".png");
                    death_state.add_frame(death_texture);
                }

                death_state.set_timer(missileengine::TimerBuilder().with_interval(125ms).with_loop(false).build());
                death_state.play(true); // Play the animation
                death_state.loop(
                    false); // Loop the animation until a transition is triggered or the animation is stopped

                sprite_animation.add_state("death", death_state);

                sprite_animation.force_transition_to("run");
            })
        .with_component_using_function<missileengine::Rigidbody2dComponent>([](auto &rigidbody)
                                                                            { rigidbody.set_static(false); })
        .with_component<missileengine::BoxCollider2dComponent>()
        .with_component<missiletoad::MechaMoscaComponent>()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                transform.position = glm::vec2{pos_x, pos_y};
                transform.scale    = {player_transform_scale};
            })
        .with_component_using_function<missileengine::SpriteComponent>(
            [&](auto &sprite)
            {
                constexpr uint32_t player_z_index = 100;
                sprite.z_index                    = player_z_index;
            },
            game.asset_manager().load<missileengine::Texture>(
                "/assets/sprites/enemies/mecha_mosquito/move_idle/mecha1.png"))
        .with_component<missiletoad::HealthComponent>()
        .with_tag("Enemy")
        .build();
}
