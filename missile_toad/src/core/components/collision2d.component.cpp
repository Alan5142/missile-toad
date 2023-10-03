
#include "missile_toad/core/components/collision2d.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::Collision2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::Collision2dComponent>(ctx)
        .type("missiletoad::core::Collision2dComponent"_hs)
        .ctor<>();
}
