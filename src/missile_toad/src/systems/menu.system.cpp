
#include "missile_toad/systems/menu.system.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::MenuSystem::MenuSystem(missileengine::Game *game)
{
    // TODO: Add your constructor code here
    spdlog::trace("game::MenuSystem() called.");
    unused(game);
    spdlog::trace("game::MenuSystem() called.");
}

void missiletoad::MenuSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::MenuSystem>(ctx)
        .type("missiletoad::MenuSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}
