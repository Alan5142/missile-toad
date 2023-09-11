
#include "missile_toad/core/systems/renderer.system.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void core::RendererSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<core::RendererSystem>(ctx)
        .type("core::RendererSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<>();
}

void core::RendererSystem::on_render()
{
}
