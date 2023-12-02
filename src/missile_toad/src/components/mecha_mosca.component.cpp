
#include "missile_toad/components/mecha_mosca.component.hpp"
#include "missile_toad/components/health.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::MechaMoscaComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::MechaMoscaComponent>(ctx).type("missiletoad::MechaMoscaComponent"_hs).ctor<>();
}
