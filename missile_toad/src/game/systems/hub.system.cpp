
#include "missile_toad/game/systems/hub.system.hpp"
#include "missile_toad/core/asset_manager.hpp"
#include "missile_toad/core/core_components.hpp"
#include "missile_toad/core/game.hpp"
#include "missile_toad/game/components/player.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::game::HubSystem::HubSystem(missiletoad::core::Game *game)
{
    // TODO: Add your constructor code here
    spdlog::trace("game::HubSystem() called.");

    unused(game);
    spdlog::trace("game::HubSystem() called.");
}

void missiletoad::game::HubSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::game::HubSystem>(ctx)
        .type("missiletoad::game::HubSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<missiletoad::core::Game *>();
    // TODO: Add your register code here
}

void missiletoad::game::HubSystem::on_start()
{
    spdlog::trace("game::HubSystem::on_start() called.");
    auto &game           = missiletoad::core::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto  ldtk_project   = game.asset_manager().load<ldtk::Project>("/assets/testRoom.ldtk");
    game.active_scene().segment_loader(*ldtk_project, "", 0, {{"Room", 0, true}, {"Ground", 0, false}});

    // Create camera
    auto  camera_entity    = scene_entities.create();
    auto &camera           = scene_entities.emplace<missiletoad::core::Camera2dComponent>(camera_entity);
    auto &camera_transform = scene_entities.emplace<missiletoad::core::TransformComponent>(camera_entity);

    camera_transform.position = {0.0f, 0.0f};
    camera.set_zoom(1.0f);

    // Create player
    auto player_entity = scene_entities.create();

    auto &player_transform    = scene_entities.emplace<missiletoad::core::TransformComponent>(player_entity);
    player_transform.position = {};
    scene_entities.patch<core::TransformComponent>(player_entity);

    auto  player_texture = game.asset_manager().load<missiletoad::core::Texture>("/assets/mt.png");
    auto &sprite         = scene_entities.emplace<missiletoad::core::SpriteComponent>(player_entity, player_texture);

    constexpr auto player_z_index = 100;
    sprite.z_index                = player_z_index;

    auto &rigidbody = scene_entities.emplace<missiletoad::core::Rigidbody2dComponent>(player_entity);
    rigidbody.set_static(false);
    scene_entities.emplace<missiletoad::core::BoxCollider2dComponent>(player_entity);

    scene_entities.emplace<missiletoad::game::PlayerComponent>(player_entity);
}
