
#include "missile_engine/components/sprite.component.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void texture_setter(missilengine::SpriteComponent &self, const std::string &path)
{
    auto &game = missilengine::Game::get_instance();

    self.texture = game.asset_manager().load<missilengine::Texture>(path);
}

void missilengine::SpriteComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missilengine::SpriteComponent>(ctx)
        .type("missilengine::SpriteComponent"_hs)
        .data<&texture_setter, &missilengine::SpriteComponent::texture>("texture"_hs)
        .data<&missilengine::SpriteComponent::z_index>("z_index"_hs)
        .ctor<>();
}
