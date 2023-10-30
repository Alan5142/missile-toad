#include "missile_engine/components/transform.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::TransformComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::TransformComponent>(ctx)
        .type("missileengine::TransformComponent"_hs)
        .data<&missileengine::TransformComponent::position>("position"_hs)
        .data<&missileengine::TransformComponent::scale>("scale"_hs)
        .data<&missileengine::TransformComponent::rotation>("rotation"_hs)
        .ctor<>();
}
