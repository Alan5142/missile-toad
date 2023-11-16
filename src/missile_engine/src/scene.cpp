/// @file missile_toad/src/core/scene.cpp

#include "missile_engine/scene.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/systems/audio.system.hpp"
#include "missile_engine/systems/movie_player.system.hpp"
#include "missile_engine/systems/physics.system.hpp"
#include "missile_engine/systems/renderer.system.hpp"
#include "missile_engine/systems/sprite_animation.system.hpp"

void missileengine::Scene::on_start()
{
    spdlog::trace("Scene::on_start() called.");

    for (auto &system : systems_)
    {
        system->on_start();
    }

    spdlog::trace("Scene::on_start() finished.");
}
void missileengine::Scene::on_destroy()
{
    spdlog::trace("Scene::on_destroy() called.");

    for (auto &system : systems_)
    {
        system->on_destroy();
    }

    spdlog::trace("Scene::on_destroy() finished.");
}

void missileengine::Scene::update(float delta_time)
{
    spdlog::trace("Scene::update() called.");

    for (auto &system : systems_)
    {
        system->on_update(delta_time);
    }

    spdlog::trace("Scene::update() finished.");
}

void missileengine::Scene::fixed_update(float delta_time)
{
    spdlog::trace("Scene::fixed_update() called.");

    for (auto &system : systems_)
    {
        system->on_fixed_update(delta_time);
    }

    spdlog::trace("Scene::fixed_update() finished.");
}

void missileengine::Scene::on_render()
{
    spdlog::trace("Scene::on_render() called.");

    for (auto &system : systems_)
    {
        system->on_render();
    }

    spdlog::trace("Scene::on_render() finished.");
}

missileengine::Scene::Scene(missileengine::Game *game) : game_(game)
{
    spdlog::trace("Scene::Scene() called.");

    spdlog::trace("Scene::Scene() finished.");
}

void missileengine::Scene::on_post_init()
{
    // Load the systems.
    this->systems_.emplace_back(std::make_unique<PhysicsSystem>(game_));
    this->systems_.emplace_back(std::make_unique<SpriteAnimationSystem>(game_));
    this->systems_.emplace_back(std::make_unique<AudioSystem>(game_));
    this->systems_.emplace_back(std::make_unique<MoviePlayerSystem>(game_));
    this->systems_.emplace_back(std::make_unique<RendererSystem>(game_));
}

void missileengine::Scene::segment_loader(ldtk::Project &project, std::string_view ldtk_world, int level_id,
                                          const std::vector<LayerInfo>             &layers,
                                          std::function<void(const ldtk::Entity &)> on_entity_create)
{
    // get a world
    const auto &world = project.getWorld(ldtk_world.data());

    // get a level
    const auto &level = world.getLevel(level_id);

    // get a layer

    for (const auto &[layer_name, z_index, has_collider] : layers)
    {
        const auto &current_layer = level.getLayer(layer_name);
        if (current_layer.hasTileset())
        {
            auto texture = game_->asset_manager().load<missileengine::Texture>("/assets/levels/" +
                                                                               current_layer.getTileset().path);

            // iterate on the tiles of the layer
            for (const auto &tile : current_layer.allTiles())
            {
                const auto &position     = tile.getGridPosition();
                const auto &texture_rect = tile.getTextureRect();

                auto &registry = game_->active_scene().get_registry();
                auto  entity   = registry.create();

                auto &transform    = registry.emplace<missileengine::TransformComponent>(entity);
                transform.position = {position.x, position.y};
                transform.rotation = 0.0f;
                transform.scale    = {1.0f, 1.0f};

                auto &sprite    = registry.emplace<missileengine::SpriteComponent>(entity, texture);
                sprite.texture  = texture;
                sprite.scissors = {texture_rect.x, texture_rect.y, texture_rect.width, texture_rect.height};
                sprite.z_index  = z_index;

                if (has_collider)
                {
                    registry.emplace<missileengine::BoxCollider2dComponent>(entity);
                }

                registry.emplace<missileengine::TagComponent>(entity, layer_name);
            }
        }

        for (const auto &entity : current_layer.allEntities())
        {
            on_entity_create(entity);
        }
    }
}

entt::entity missileengine::Scene::get_entity_with_tag(std::string_view tag)
{
    auto view = scene_entities_.view<TagComponent>();
    for (auto entity : view)
    {
        auto &tag_component = view.get<TagComponent>(entity);
        if (tag_component.tag == tag)
        {
            return entity;
        }
    }

    return entt::null;
}

missileengine::EntityBuilder missileengine::Scene::create_entity()
{
    return {&scene_entities_};
}
