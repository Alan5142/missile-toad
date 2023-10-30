
#include "missile_engine/components/collision2d.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::Collision2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::Collision2dComponent>(ctx).type("missileengine::Collision2dComponent"_hs).ctor<>();
}
