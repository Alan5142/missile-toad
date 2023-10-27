
#include "missile_engine/components/camera_2d.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missilengine::Camera2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missilengine::Camera2dComponent>(ctx)
        .type("missilengine::Camera2dComponent"_hs)
        .data<&missilengine::Camera2dComponent::set_zoom, &missilengine::Camera2dComponent::get_zoom>("zoom"_hs)
        .data<&missilengine::Camera2dComponent::set_target, &missilengine::Camera2dComponent::get_target>("target"_hs)
        .data<&missilengine::Camera2dComponent::set_offset, &missilengine::Camera2dComponent::get_offset>("offset"_hs)
        .ctor<>();
}
