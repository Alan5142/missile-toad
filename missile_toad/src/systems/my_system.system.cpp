
#include "missile_toad/systems/my_system.system.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::MySystemSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::MySystemSystem>(ctx)
        .type("missiletoad::MySystemSystem"_hs)
        .base<missiletoad::BaseSystem>()
        .ctor<>();
}