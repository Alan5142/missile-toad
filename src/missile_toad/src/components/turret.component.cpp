
#include "missile_toad/components/turret.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::TurretComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::TurretComponent>(ctx).type("missiletoad::TurretComponent"_hs).ctor<>();
}