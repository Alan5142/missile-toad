
#include "missile_toad/core/components/camera_2d.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::Camera2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::Camera2dComponent>(ctx)
        .type("missiletoad::core::Camera2dComponent"_hs)
        .data<&missiletoad::core::Camera2dComponent::set_zoom, &missiletoad::core::Camera2dComponent::get_zoom>(
            "zoom"_hs)
        .data<&missiletoad::core::Camera2dComponent::set_target, &missiletoad::core::Camera2dComponent::get_target>(
            "target"_hs)
        .data<&missiletoad::core::Camera2dComponent::set_rotation, &missiletoad::core::Camera2dComponent::get_rotation>(
            "rotation"_hs)
        .data<&missiletoad::core::Camera2dComponent::set_offset, &missiletoad::core::Camera2dComponent::get_offset>(
            "offset"_hs)
        .ctor<>();
}
