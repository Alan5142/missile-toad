
#include "missile_toad/components/bullet.component.hpp"
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>


void missiletoad::BulletComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::BulletComponent>(ctx)
            .type("missiletoad::BulletComponent"_hs)
            .ctor<>();
}