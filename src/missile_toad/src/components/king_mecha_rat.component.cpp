
#include "missile_toad/components/king_mecha_rat.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::KingMechaRatComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::KingMechaRatComponent>(ctx).type("missiletoad::KingMechaRatComponent"_hs).ctor<>();
}
