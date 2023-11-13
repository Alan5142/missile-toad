
#include "missile_toad/systems/hub.system.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/better_camera.component.hpp"
#include "missile_toad/components/player.component.hpp"
#include "missile_toad/components/turret.component.hpp"
#include "missile_toad/systems/camera.system.hpp"

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

void missiletoad::HubSystem::on_start()
{
    spdlog::trace("game::HubSystem::on_start() called.");
    auto &game         = missileengine::Game::get_instance();
    auto  ldtk_project = game.asset_manager().load<ldtk::Project>("/assets/levels/testRoom.ldtk");

    // TODO: To be removed in the future.
    game.active_scene().segment_loader(*ldtk_project, "", 0, {{"Room", 0, true}, {"Ground", 0, false}});

}
