#include "missile_engine/components/transform.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missilengine::TransformComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missilengine::TransformComponent>(ctx)
        .type("missilengine::TransformComponent"_hs)
        .data<&missilengine::TransformComponent::position>("position"_hs)
        .data<&missilengine::TransformComponent::scale>("scale"_hs)
        .data<&missilengine::TransformComponent::rotation>("rotation"_hs)
        .ctor<>();
}
