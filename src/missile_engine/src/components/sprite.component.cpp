
#include "missile_engine/components/sprite.component.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void texture_setter(missileengine::SpriteComponent &self, const std::string &path)
{
    auto &game = missileengine::Game::get_instance();

    self.texture = game.asset_manager().load<missileengine::Texture>(path);
}

void missileengine::SpriteComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::SpriteComponent>(ctx)
        .type("missileengine::SpriteComponent"_hs)
        .data<&texture_setter, &missileengine::SpriteComponent::texture>("texture"_hs)
        .data<&missileengine::SpriteComponent::z_index>("z_index"_hs)
        .ctor<>();
}
