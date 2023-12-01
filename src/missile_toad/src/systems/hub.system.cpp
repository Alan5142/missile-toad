
#include "missile_toad/systems/hub.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/components/circle_collider_2d.component.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/bullet_utils.hpp"
#include "missile_toad/components/better_camera.component.hpp"
#include "missile_toad/components/mecha_mosca.component.hpp"
#include "missile_toad/components/player.component.hpp"
#include "missile_toad/components/turret.component.hpp"
#include "missile_toad/enemy_utils.hpp"
#include "missile_toad/systems/camera.system.hpp"
#include "missile_toad/systems/enemy.system.hpp"

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

void on_create_entity(const ldtk::Entity &entity)
{
    if (entity.getName() == "MechaMosca")
    {
        missiletoad::createMechaMosquito(static_cast<float>(entity.getPosition().x) / missileengine::PIXELS_PER_UNIT,
                                         static_cast<float>(entity.getPosition().y) / missileengine::PIXELS_PER_UNIT);
    }
    else if (entity.getName() == "Experimento_M")
    {
        missiletoad::createExpM(static_cast<float>(entity.getPosition().x) / missileengine::PIXELS_PER_UNIT,
                                static_cast<float>(entity.getPosition().y) / missileengine::PIXELS_PER_UNIT);
    }
}

void missiletoad::HubSystem::on_start()
{
    spdlog::trace("game::HubSystem::on_start() called.");
    auto &game  = missileengine::Game::get_instance();
    auto &scene = game.active_scene();

    auto ldtk_project = game.asset_manager().load<ldtk::Project>("/assets/levels/testRoom.ldtk");

    // get a world
    auto &world = ldtk_project->getWorld("");

    // TODO: To be removed in the future.
    for (const auto &level : world.allLevels())
    {
        game.active_scene().segment_loader(
            world, level.name, {{"Room", 0, true}, {"Ground", 0, false}, {"Enemies", 0, false}}, on_create_entity);
    }

    // Add camera system
    scene.add_system<missiletoad::CameraSystem>();

    auto view = scene.view<missileengine::SpriteAnimationComponent>();

    for (auto entity : view)
    {
        auto &sprite_animation = view.get<missileengine::SpriteAnimationComponent>(entity);
        sprite_animation.force_transition_to("run"); // Waits for the current animation to finish
    }

    scene.add_system<missiletoad::EnemySystem>();

    auto music = game.asset_manager().load<missileengine::Music>("/assets/sounds/song1.mp3");
    music->get_music().Play();
    music->get_music().SetVolume(0.8F);

    scene.create_entity().with_component<missileengine::AudioComponent>(music).build();
}
