
#include "missile_toad/game/components/player.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::game::PlayerComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::game::PlayerComponent>(ctx).type("missiletoad::game::PlayerComponent"_hs).ctor<>();
}
