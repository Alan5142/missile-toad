#include "missile_toad/core/scene.hpp"
#include "missile_toad/core/components/box_collider_2d.component.hpp"
#include "missile_toad/core/components/rigidbody_2d.component.hpp"
#include "missile_toad/core/components/sprite.component.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include <entt/locator/locator.hpp>

void missiletoad::core::Scene::on_start()
{
    spdlog::trace("Scene::on_start() called.");

    for (auto &system : systems_)
    {
        system->on_start();
    }

    spdlog::trace("Scene::on_start() finished.");
}
void missiletoad::core::Scene::on_destroy()
{
    spdlog::trace("Scene::on_destroy() called.");

    for (auto &system : systems_)
    {
        system->on_destroy();
    }

    spdlog::trace("Scene::on_destroy() finished.");
}

void missiletoad::core::Scene::update(float delta_time)
{
    spdlog::trace("Scene::update() called.");

    for (auto &system : systems_)
    {
        system->on_update(delta_time);
    }

    for (auto entity :
         scene_entities_.view<core::SpriteComponent, core::TransformComponent, core::Rigidbody2dComponent>())
    {
        //        auto &transform = scene_entities_.get<core::TransformComponent>(entity);
        auto &physics   = scene_entities_.get<core::Rigidbody2dComponent>(entity);
        auto &transform = scene_entities_.get<core::TransformComponent>(entity);

        if (physics.is_static())
        {
            continue;
        }

        auto x_velocity = 0.0F;
        auto y_velocity = 0.0F;
        if (IsKeyDown(KEY_LEFT))
        {
            x_velocity = -1;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            x_velocity = 1;
        }

        if (IsKeyDown(KEY_UP))
        {
            y_velocity = -1;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            y_velocity = 1;
        }

        if (IsKeyDown(KEY_R))
        {
            transform.rotation -= 90 * delta_time;
        }
        if (IsKeyDown(KEY_T))
        {
            transform.rotation += 90 * delta_time;
        }

        physics.set_linear_velocity({x_velocity * 5, y_velocity * 5});
        scene_entities_.patch<core::Rigidbody2dComponent>(entity);
        scene_entities_.patch<core::TransformComponent>(entity);
    }

    spdlog::trace("Scene::update() finished.");
}

void missiletoad::core::Scene::fixed_update(float delta_time)
{
    spdlog::trace("Scene::fixed_update() called.");

    for (auto &system : systems_)
    {
        system->on_fixed_update(delta_time);
    }

    spdlog::trace("Scene::fixed_update() finished.");
}

void missiletoad::core::Scene::on_render()
{
    spdlog::trace("Scene::on_render() called.");

    for (auto &system : systems_)
    {
        system->on_render();
    }

    spdlog::trace("Scene::on_render() finished.");
}

missiletoad::core::Scene::Scene()
{
    spdlog::trace("Scene::Scene() called.");

    entt::locator<Scene *>::emplace(this);
    entt::locator<entt::registry *>::emplace(&scene_entities_);

    spdlog::trace("Scene::Scene() finished.");
}
