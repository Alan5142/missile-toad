
#include "missile_engine/components/disabled.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::DisabledComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::DisabledComponent>(ctx).type("missileengine::DisabledComponent"_hs).ctor<>();
}
