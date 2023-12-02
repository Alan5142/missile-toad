#include "missile_toad/bullet_utils.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_toad/components/bullet.component.hpp"
#include "missile_toad/components/health.component.hpp"

#include <glm/glm.hpp>

void missiletoad::create_bullet(glm::vec2 start_position, glm::vec2 objetive_position, float velocity, float damage,
                                bool is_enemy_bullet)
{
    auto &game  = missileengine::Game::get_instance();
    auto &scene = game.active_scene();

    auto       bullet_texture = game.asset_manager().load<missileengine::Texture>("/assets/sprites/bullets/bala.png");
    const auto bullet_transform_scale = glm::vec2{1.0F, 1.0F};
    const auto normalized_vector      = glm::normalize(objetive_position - start_position);
    spdlog::info("Velocity {}", velocity);
    spdlog::info("Damage {}", damage);

    scene.create_entity()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](auto &transform)
            {
                transform.position = normalized_vector * 1.2F + start_position;
                transform.scale    = {bullet_transform_scale};
            })
        .with_component_using_function<missileengine::SpriteComponent>(
            [&](auto &sprite)
            {
                constexpr uint32_t bullet_z_index = 101;
                sprite.z_index                    = bullet_z_index;
            },
            std::move(bullet_texture))
        .with_component_using_function<missileengine::Rigidbody2dComponent>(
            [](auto &rigidbody)
            {
                rigidbody.set_static(false);
                rigidbody.set_is_bullet(true);
            })
        .with_component<missileengine::BoxCollider2dComponent>()
        .with_component<missiletoad::BulletComponent>(velocity, normalized_vector)
        .with_component<missileengine::Collision2dComponent>(
            [&, damage, velocity, is_enemy_bullet](auto self, auto other, auto status)
            {
                auto &game         = missileengine::Game::get_instance();
                auto &scene        = game.active_scene();
                bool  is_colliding = status == missileengine::ECollisionStatus::ENTER;

                spdlog::info("Velocity {}", velocity);
                spdlog::info("Damage {}", damage);
                if (!scene.get_registry().valid(other))
                {

                    scene.get_registry().destroy(self);
                    return;
                }
                auto other_tag = scene.try_get_component<missileengine::TagComponent>(other);

                if (other_tag == nullptr)
                {
                    spdlog::info("No tag found");
                    return;
                }

                spdlog::info("Other tag: {}", other_tag->tag);

                if (is_colliding && other_tag->tag == "Room")
                {

                    spdlog::info("Collission happening with Room");
                    scene.get_registry().destroy(self);
                }
                else if (is_colliding && other_tag->tag == "Enemy")
                {
                    spdlog::info("Collission happening with Enemy");
                    auto &health = scene.get_registry().get<missiletoad::HealthComponent>(other);

                    if (!is_enemy_bullet)
                    {
                        health.take_damage(damage);
                        scene.get_registry().destroy(self);
                    }
                    else
                    {
                        scene.get_registry().destroy(self);
                    }
                }
                else if (is_colliding && other_tag->tag == "Player")
                {
                    auto &health = scene.get_registry().get<missiletoad::HealthComponent>(other);

                    if (is_enemy_bullet)
                    {
                        health.take_damage(damage);
                        scene.get_registry().destroy(self);
                    }
                    else
                    {
                        scene.get_registry().destroy(self);
                    }
                }
                else if (scene.try_get_component<missiletoad::BulletComponent>(other) != nullptr)
                {
                    scene.get_registry().destroy(self);
                }
                else
                {
                    spdlog::info("Collission happening with unknown object");
                }
            })
        .build();
}
