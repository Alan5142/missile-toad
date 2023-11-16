
#include "missile_toad/systems/enemy.system.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
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
    auto view = scene.view<missiletoad::MechaMoscaComponent>();
    for (auto entity : view)
    {
        auto &enemy = view.get<missiletoad::MechaMoscaComponent>(entity);
        if (enemy.state_machine.is("follow"_s))
        {
            auto &player_transform = scene.get_component<missileengine::TransformComponent>(player_entity);
            auto &transform        = scene.get_component<missileengine::TransformComponent>(entity);
            auto &rigidbody        = scene.get_component<missileengine::Rigidbody2dComponent>(entity);
            auto  direction        = player_transform.position - transform.position;
            // 2D Vector
            auto normalized_direction = glm::normalize(direction);
            rigidbody.set_linear_velocity(normalized_direction * enemy.enemy_speed);
        }
    }
}
