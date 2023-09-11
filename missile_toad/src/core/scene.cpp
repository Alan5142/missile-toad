#include "missile_toad/core/scene.hpp"
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

    for (auto entity : scene_entities_.view<core::SpriteComponent, core::TransformComponent>())
    {
        auto &transform = scene_entities_.get<core::TransformComponent>(entity);

        if (IsKeyDown(KEY_LEFT))
        {
            transform.position.x += 20 * delta_time;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            transform.position.x -= 20 * delta_time;
        }

        if (IsKeyDown(KEY_UP))
        {
            transform.position.y += 20 * delta_time;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            transform.position.y -= 20 * delta_time;
        }

        if (IsKeyDown(KEY_A))
        {
            transform.rotation -= 20 * delta_time;
        }

        if (IsKeyDown(KEY_D))
        {
            transform.rotation += 20 * delta_time;
        }
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
