
#include "missile_engine/components/audio.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missilengine::AudioComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missilengine::AudioComponent>(ctx).type("missilengine::AudioComponent"_hs).ctor<>();
}
