
#include "missile_toad/core/components/audio.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::AudioComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::AudioComponent>(ctx).type("missiletoad::core::AudioComponent"_hs).ctor<>();
}
