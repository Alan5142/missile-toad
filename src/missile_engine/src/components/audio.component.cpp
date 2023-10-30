
#include "missile_engine/components/audio.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::AudioComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::AudioComponent>(ctx).type("missileengine::AudioComponent"_hs).ctor<>();
}
