/// @file missile_toad/src/core/scene.cpp

#include "missile_toad/core/scene.hpp"
#include "missile_toad/core/game.hpp"
#include "missile_toad/core/systems/physics.system.hpp"
#include "missile_toad/core/systems/renderer.system.hpp"
#include "missile_toad/core/systems/sprite_animation.system.hpp"

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

missiletoad::core::Scene::Scene(missiletoad::core::Game &game)
{
    spdlog::trace("Scene::Scene() called.");

    // Load the systems.
    this->systems_.emplace_back(std::make_unique<PhysicsSystem>(&game));
    this->systems_.emplace_back(std::make_unique<RendererSystem>(&game));
    this->systems_.emplace_back(std::make_unique<SpriteAnimationSystem>(&game));

    // Call the on_start() method of all the systems.
    on_start();

    spdlog::trace("Scene::Scene() finished.");
}
