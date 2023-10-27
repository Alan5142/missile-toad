
#include "missile_engine/components/collision2d.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missilengine::Collision2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missilengine::Collision2dComponent>(ctx).type("missilengine::Collision2dComponent"_hs).ctor<>();
}
