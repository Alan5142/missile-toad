
#include "missile_engine/components/line_renderer.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::LineRendererComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::LineRendererComponent>(ctx).type("missileengine::LineRendererComponent"_hs).ctor<>();
}
