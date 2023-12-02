
#include "missile_toad/components/caracool.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::CaracoolComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::CaracoolComponent>(ctx).type("missiletoad::CaracoolComponent"_hs).ctor<>();
}
