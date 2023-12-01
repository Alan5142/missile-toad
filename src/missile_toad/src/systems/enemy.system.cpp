
#include "missile_toad/systems/enemy.system.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_toad/bullet_utils.hpp"
#include "missile_toad/components/caracool.component.hpp"
#include "missile_toad/components/experimento_m.component.hpp"
#include "missile_toad/components/health.component.hpp"
#include "missile_toad/components/king_mecha_rat.component.hpp"
#include "missile_toad/components/mecha_mosca.component.hpp"
#include "missile_toad/components/player.component.hpp"
#include "missile_toad/enemy_utils.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

missiletoad::EnemySystem::EnemySystem(missileengine::Game *game)
{
    unused(game);
    // TODO: Add your constructor code here
}

void missiletoad::EnemySystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::EnemySystem>(ctx)
        .type("missiletoad::EnemySystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}

void missiletoad::EnemySystem::on_start()
{
}

void missiletoad::EnemySystem::on_update(float delta_time)
{
    unused(delta_time);
    using namespace boost::sml;
    auto &game  = missileengine::Game::get_instance();
    auto &scene = game.active_scene();

    entt::entity player_entity = entt::null;
    for (auto entity : scene.view<missiletoad::PlayerComponent>())
    {
        player_entity = entity;
    }

    // TODO: deberia ser mecamosquito
    auto view_mecha_mosca = scene.view<missiletoad::MechaMoscaComponent>();
    for (auto entity : view_mecha_mosca)
    {
        auto &player_transform = scene.get_component<missileengine::TransformComponent>(player_entity);
        auto &transform        = scene.get_component<missileengine::TransformComponent>(entity);
        auto &rigidbody        = scene.get_component<missileengine::Rigidbody2dComponent>(entity);
        auto &sprite           = scene.get_component<missileengine::SpriteComponent>(entity);
        auto &health           = scene.get_component<missiletoad::HealthComponent>(entity);
        auto &animation        = scene.get_component<missileengine::SpriteAnimationComponent>(entity);
        auto &enemy            = view_mecha_mosca.get<missiletoad::MechaMoscaComponent>(entity);

        if (enemy.state_machine.is("follow"_s))
        {

            auto direction = player_transform.position - transform.position;
            // 2D Vector
            auto normalized_direction = glm::normalize(direction);
            rigidbody.set_linear_velocity(normalized_direction * enemy.enemy_speed);

            sprite.color = glm::mix(glm::u8vec4{255, 255, 255, 255}, glm::u8vec4{255, 0, 0, 255},
                                    1.0F - health.get_health_percentage());

            if (direction.x < 0.0F)
            {
                sprite.flip_x = false;
            }
            else
            {
                sprite.flip_x = true;
            }

            if (health.is_dead())
            {
                sprite.color = glm::u8vec4{255, 255, 255, 255};
                rigidbody.set_linear_velocity({0.0F, 0.0F});
                enemy.state_machine.process_event(missiletoad::MechaMoscaDeathEvent());
                animation.force_transition_to("death");
            }
        }
        else if (enemy.state_machine.is("death"_s))
        {
            auto &sprite_animation = scene.get_component<missileengine::SpriteAnimationComponent>(entity);
            if (!sprite_animation.is_playing())
            {

                scene.get_registry().destroy(entity);
            }
        }
    }

    auto view_exp_m = scene.view<missiletoad::ExperimentoMComponent>();
    for (auto entity : view_exp_m)
    {
        auto &player_transform = scene.get_component<missileengine::TransformComponent>(player_entity);
        auto &transform        = scene.get_component<missileengine::TransformComponent>(entity);
        auto &rigidbody        = scene.get_component<missileengine::Rigidbody2dComponent>(entity);
        auto &sprite           = scene.get_component<missileengine::SpriteComponent>(entity);
        auto &health           = scene.get_component<missiletoad::HealthComponent>(entity);
        auto &animation        = scene.get_component<missileengine::SpriteAnimationComponent>(entity);
        auto &enemy            = view_exp_m.get<missiletoad::ExperimentoMComponent>(entity);
        if (enemy.state_machine.is("follow"_s))
        {

            auto direction = player_transform.position - transform.position;
            // 2D Vector
            auto normalized_direction = glm::normalize(direction);
            rigidbody.set_linear_velocity(normalized_direction * enemy.enemy_speed);
            if (glm::length(direction) < 5.0F)
            {
                enemy.state_machine.process_event(missiletoad::ExperimentoAttackEvent());
                animation.force_transition_to("attack");
            }
        }
        else if (enemy.state_machine.is("attack"_s))
        {
            auto  direction        = player_transform.position - transform.position;
            auto &sprite_animation = scene.get_component<missileengine::SpriteAnimationComponent>(entity);
            if (direction.x < 0.0F)
            {
                sprite.flip_x = true;
            }
            else
            {
                sprite.flip_x = false;
            }

            rigidbody.set_linear_velocity({0.0F, 0.0F});

            if (!sprite_animation.is_playing())
            {
                createBullet(transform.position, player_transform.position, 5.0F, 10.0F, true);
                enemy.state_machine.process_event(missiletoad::ExperimentoMIdleEvent());
                animation.get_state().play(true);
                animation.force_transition_to("idle");
            }
        }
        else if (enemy.state_machine.is("idle"_s))
        {
            auto &sprite_animation = scene.get_component<missileengine::SpriteAnimationComponent>(entity);

            if (!sprite_animation.is_playing())
            {
                enemy.state_machine.process_event(missiletoad::ExperimentoMMoveEvent());
                animation.get_state().play(true);
                animation.force_transition_to("run");
            }
        }
        else if (enemy.state_machine.is("death"_s))
        {
            auto &sprite_animation = scene.get_component<missileengine::SpriteAnimationComponent>(entity);
            if (!sprite_animation.is_playing())
            {

                scene.get_registry().destroy(entity);
            }
        }

        sprite.color = glm::mix(glm::u8vec4{255, 255, 255, 255}, glm::u8vec4{255, 0, 0, 255},
                                1.0F - health.get_health_percentage());
        if (health.is_dead())
        {
            sprite.color = glm::u8vec4{255, 255, 255, 255};
            rigidbody.set_linear_velocity({0.0F, 0.0F});
            enemy.state_machine.process_event(missiletoad::ExperimentoMDeathEvent());
            animation.force_transition_to("death");
        }
    }
}
