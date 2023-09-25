
#include "missile_toad/core/components/sprite.component.hpp"
#include "missile_toad/core/asset_manager.hpp"
#include "missile_toad/core/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void texture_setter(missiletoad::core::SpriteComponent &self, const std::string &path)
{
    auto &game = missiletoad::core::Game::get_instance();

    self.texture = game.asset_manager().load<missiletoad::core::Texture>(path);
}

void missiletoad::core::SpriteComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::SpriteComponent>(ctx)
        .type("missiletoad::core::SpriteComponent"_hs)
        .data<&texture_setter, &missiletoad::core::SpriteComponent::texture>("texture"_hs)
        .data<&missiletoad::core::SpriteComponent::z_index>("z_index"_hs)
        .ctor<>();
}
