
#include "missile_toad/systems/hub.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_toad/components/player.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::HubSystem::HubSystem(missilengine::Game *game)
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
        .base<missilengine::BaseSystem>()
        .ctor<missilengine::Game *>();
    // TODO: Add your register code here
}

void missiletoad::HubSystem::on_start()
{
    spdlog::trace("game::HubSystem::on_start() called.");
    auto &game           = missilengine::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto  ldtk_project   = game.asset_manager().load<ldtk::Project>("/assets/testRoom.ldtk");

    // TODO: To be removed in the future.
    game.active_scene().segment_loader(*ldtk_project, "", 0, {{"Room", 0, true}, {"Ground", 0, false}});

    // Create camera
    auto camera_entity = scene_entities.create();
    scene_entities.emplace<missilengine::Camera2dComponent>(camera_entity);
    auto &camera_transform = scene_entities.emplace<missilengine::TransformComponent>(camera_entity);

    camera_transform.position = {};

    // Create player
    auto player_entity = scene_entities.create();

    auto &player_transform    = scene_entities.emplace<missilengine::TransformComponent>(player_entity);
    player_transform.position = {};
    scene_entities.patch<missilengine::TransformComponent>(player_entity);

    auto  player_texture = game.asset_manager().load<missilengine::Texture>("/assets/mt.png");
    auto &sprite         = scene_entities.emplace<missilengine::SpriteComponent>(player_entity, player_texture);

    constexpr auto player_z_index = 100;
    sprite.z_index                = player_z_index;

    auto &rigidbody = scene_entities.emplace<missilengine::Rigidbody2dComponent>(player_entity);
    rigidbody.set_static(false);
    scene_entities.emplace<missilengine::BoxCollider2dComponent>(player_entity);

    scene_entities.emplace<missiletoad::PlayerComponent>(player_entity);
}
