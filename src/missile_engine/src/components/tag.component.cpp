
#include "missile_engine/components/tag.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::TagComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::TagComponent>(ctx).type("missileengine::TagComponent"_hs).ctor<>();
}
