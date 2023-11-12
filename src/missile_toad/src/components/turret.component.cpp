
#include "missile_toad/components/turret.component.hpp"
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>


void missiletoad::TurretComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::TurretComponent>(ctx)
            .type("missiletoad::TurretComponent"_hs)
            .ctor<>();
}