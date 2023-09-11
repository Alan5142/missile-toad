
#include "missile_toad/core/components/camera_2d.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::Camera2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::Camera2dComponent>(ctx)
        .type("missiletoad::core::Camera2dComponent"_hs)
        .data<&missiletoad::core::Camera2dComponent::camera>("camera"_hs)
        .ctor<>();
}
