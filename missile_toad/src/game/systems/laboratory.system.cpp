
#include "missile_toad/game/systems/laboratory.system.hpp"
#include "missile_toad/core/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::game::LaboratorySystem::LaboratorySystem(missiletoad::core::Game *game)
{
    // TODO: Add your constructor code here
    spdlog::trace("game::LaboratorySystem() called.");
    unused(game);
    spdlog::trace("game::LaboratorySystem() called.");
}

void missiletoad::game::LaboratorySystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::game::LaboratorySystem>(ctx)
        .type("missiletoad::game::LaboratorySystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<missiletoad::core::Game *>();
    // TODO: Add your register code here
}