
#include "missile_toad/components/health.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::HealthComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::HealthComponent>(ctx).type("missiletoad::HealthComponent"_hs).ctor<>();
}
