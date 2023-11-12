
#include "missile_engine/components/movie_player.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::MoviePlayerComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::MoviePlayerComponent>(ctx).type("missileengine::MoviePlayerComponent"_hs).ctor<>();
}
