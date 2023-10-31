
#include "missile_toad/components/better_camera.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::BetterCameraComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::BetterCameraComponent>(ctx).type("missiletoad::BetterCameraComponent"_hs).ctor<>();
}
