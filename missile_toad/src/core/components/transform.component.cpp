#include "missile_toad/core/components/transform.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::TransformComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::TransformComponent>(ctx)
        .type("missiletoad::core::TransformComponent"_hs)
        .data<&missiletoad::core::TransformComponent::position>("position"_hs)
        .data<&missiletoad::core::TransformComponent::scale>("scale"_hs)
        .data<&missiletoad::core::TransformComponent::rotation>("rotation"_hs)
        .ctor<>();
}
