
#include "missile_toad/game/systems/menu.system.hpp"
#include "missile_toad/core/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::game::MenuSystem::MenuSystem(missiletoad::core::Game *game)
{
    // TODO: Add your constructor code here
    spdlog::trace("game::MenuSystem() called.");
    unused(game);
    spdlog::trace("game::MenuSystem() called.");
}

void missiletoad::game::MenuSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::game::MenuSystem>(ctx)
        .type("missiletoad::game::MenuSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<missiletoad::core::Game *>();
    // TODO: Add your register code here
}