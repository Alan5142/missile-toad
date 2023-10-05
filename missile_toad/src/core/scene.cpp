/// @file missile_toad/src/core/scene.cpp

#include "missile_toad/core/scene.hpp"
#include "missile_toad/core/asset_manager.hpp"
#include "missile_toad/core/components/box_collider_2d.component.hpp"
#include "missile_toad/core/components/camera_2d.component.hpp"
#include "missile_toad/core/components/rigidbody_2d.component.hpp"
#include "missile_toad/core/components/sprite.component.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include "missile_toad/core/game.hpp"
#include "missile_toad/core/input_manager.hpp"
#include "missile_toad/core/systems/audio.system.hpp"
#include "missile_toad/core/systems/physics.system.hpp"
#include "missile_toad/core/systems/renderer.system.hpp"
#include "missile_toad/core/systems/sprite_animation.system.hpp"

struct PlayerComponent
{
};

void missiletoad::core::Scene::on_start()
{
    spdlog::trace("Scene::on_start() called.");

    for (auto &system : systems_)
    {
        system->on_start();
    }

    auto ldtk_project = game_->asset_manager().load<ldtk::Project>("/assets/testRoom.ldtk");
    this->segment_loader(*ldtk_project, "", 0, {{"Room", 0, true}, {"Ground", 0, false}});

    auto  camera_entity    = scene_entities_.create();
    auto &camera           = scene_entities_.emplace<missiletoad::core::Camera2dComponent>(camera_entity);
    auto &camera_transform = scene_entities_.emplace<missiletoad::core::TransformComponent>(camera_entity);

    camera_transform.position = {0.0f, 0.0f};
    camera.set_zoom(1.0f);

    // Create player
    auto  player_entity       = scene_entities_.create();
    auto &player_transform    = scene_entities_.emplace<missiletoad::core::TransformComponent>(player_entity);
    player_transform.position = {3.0f, 3.0f};
    auto  player_texture      = game_->asset_manager().load<missiletoad::core::Texture>("/assets/mt.png");
    auto &sprite    = scene_entities_.emplace<missiletoad::core::SpriteComponent>(player_entity, player_texture);
    sprite.z_index  = 50;
    auto &rigidbody = scene_entities_.emplace<missiletoad::core::Rigidbody2dComponent>(player_entity);
    rigidbody.set_static(false);
    scene_entities_.emplace<missiletoad::core::BoxCollider2dComponent>(player_entity);
    scene_entities_.emplace<PlayerComponent>(player_entity);

    SetTargetFPS(60);

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

    for (auto entity : scene_entities_.view<missiletoad::core::Rigidbody2dComponent, PlayerComponent>())
    {
        auto &rigidbody = scene_entities_.get<missiletoad::core::Rigidbody2dComponent>(entity);
        using missiletoad::core::EKey;

        auto linear_impulse = glm::vec2(0.0f, 0.0f);
        if (game_->input_manager().is_key_down(EKey::LEFT))
        {
            linear_impulse.x -= 1.0f;
        }
        if (game_->input_manager().is_key_down(EKey::RIGHT))
        {
            linear_impulse.x += 1.0f;
        }
        if (game_->input_manager().is_key_down(EKey::UP))
        {
            linear_impulse.y -= 1.0f;
        }
        if (game_->input_manager().is_key_down(EKey::DOWN))
        {
            linear_impulse.y += 1.0f;
        }
        rigidbody.set_linear_velocity(linear_impulse * 3.0F);
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

missiletoad::core::Scene::Scene(missiletoad::core::Game *game) : game_(game)
{
    spdlog::trace("Scene::Scene() called.");

    spdlog::trace("Scene::Scene() finished.");
}

void missiletoad::core::Scene::on_post_init()
{
    // Load the systems.
    this->systems_.emplace_back(std::make_unique<PhysicsSystem>(game_));
    this->systems_.emplace_back(std::make_unique<RendererSystem>(game_));
    this->systems_.emplace_back(std::make_unique<SpriteAnimationSystem>(game_));
    this->systems_.emplace_back(std::make_unique<AudioSystem>(game_));
}

void missiletoad::core::Scene::segment_loader(ldtk::Project &project, std::string_view ldtk_world, int level_id,
                                              const std::vector<LayerInfo> &layers)
{
    // get a world
    const auto &world = project.getWorld(ldtk_world.data());

    // get a level
    const auto &level = world.getLevel(level_id);

    // get a layer

    for (const auto &[layer_name, z_index, has_collider] : layers)
    {
        const auto &current_layer = level.getLayer(layer_name);
        auto        texture =
            game_->asset_manager().load<missiletoad::core::Texture>("/assets/" + current_layer.getTileset().path);

        // iterate on the tiles of the layer
        for (const auto &tile : current_layer.allTiles())
        {
            const auto &position     = tile.getGridPosition();
            const auto &texture_rect = tile.getTextureRect();

            auto &registry = game_->active_scene().get_registry();
            auto  entity   = registry.create();

            auto &transform    = registry.emplace<missiletoad::core::TransformComponent>(entity);
            transform.position = {position.x, position.y};
            transform.rotation = 0.0f;
            transform.scale    = {1.0f, 1.0f};

            auto &sprite    = registry.emplace<missiletoad::core::SpriteComponent>(entity, texture);
            sprite.texture  = texture;
            sprite.scissors = {texture_rect.x, texture_rect.y, texture_rect.width, texture_rect.height};
            sprite.z_index  = z_index;

            if (has_collider)
            {
                registry.emplace<missiletoad::core::BoxCollider2dComponent>(entity);
            }
        }
    }
}
