
#include "missile_toad/systems/health.system.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::HealthSystem::HealthSystem(missileengine::Game *game)
{
    // TODO: Add your constructor code here
    unused(game);
}

void missiletoad::HealthSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::HealthSystem>(ctx)
        .type("missiletoad::HealthSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}
