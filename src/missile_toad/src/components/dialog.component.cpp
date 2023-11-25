
#include "missile_toad/components/dialog.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::DialogComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::DialogComponent>(ctx).type("missiletoad::DialogComponent"_hs).ctor<>();
}
