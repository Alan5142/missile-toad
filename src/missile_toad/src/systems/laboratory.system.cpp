
#include "missile_toad/systems/laboratory.system.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::LaboratorySystem::LaboratorySystem(missilengine::Game *game)
{
    // TODO: Add your constructor code here
    spdlog::trace("game::LaboratorySystem() called.");
    unused(game);
    spdlog::trace("game::LaboratorySystem() called.");
}

void missiletoad::LaboratorySystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::LaboratorySystem>(ctx)
        .type("missiletoad::LaboratorySystem"_hs)
        .base<missilengine::BaseSystem>()
        .ctor<missilengine::Game *>();
    // TODO: Add your register code here
}
