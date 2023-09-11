
#include "missile_toad/core/components/sprite.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::SpriteComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::SpriteComponent>(ctx)
        .type("missiletoad::core::SpriteComponent"_hs)
        .data<&missiletoad::core::SpriteComponent::texture>("texture"_hs)
        .data<&missiletoad::core::SpriteComponent::z_index>("z_index"_hs)
        .ctor<>();
}
