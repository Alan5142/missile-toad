
#include "missile_toad/components/player.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::PlayerComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::PlayerComponent>(ctx).type("missiletoad::PlayerComponent"_hs).ctor<>();
}
