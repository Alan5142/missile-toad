#include "missile_toad/core/scene.hpp"
#include "missile_toad/core/components/physics_2d.component.hpp"
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
         scene_entities_.view<core::SpriteComponent, core::TransformComponent, core::Physics2dComponent>())
    {
        //        auto &transform = scene_entities_.get<core::TransformComponent>(entity);
        auto &physics = scene_entities_.get<core::Physics2dComponent>(entity);

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

        scene_entities_.patch<core::Physics2dComponent>(entity,
                                                        [&](auto &physics)
                                                        {
                                                            physics.set_linear_velocity(x_velocity * 5,
                                                                                        y_velocity * 5); //
                                                        });
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