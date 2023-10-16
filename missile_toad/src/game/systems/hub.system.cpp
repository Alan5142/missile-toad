
#include "missile_toad/game/systems/hub.system.hpp"
#include "missile_toad/core/game.hpp"

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