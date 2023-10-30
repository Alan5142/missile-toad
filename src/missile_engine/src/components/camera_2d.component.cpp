
#include "missile_engine/components/camera_2d.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::Camera2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::Camera2dComponent>(ctx)
        .type("missileengine::Camera2dComponent"_hs)
        .data<&missileengine::Camera2dComponent::set_zoom, &missileengine::Camera2dComponent::get_zoom>("zoom"_hs)
        .data<&missileengine::Camera2dComponent::set_target, &missileengine::Camera2dComponent::get_target>("target"_hs)
        .data<&missileengine::Camera2dComponent::set_offset, &missileengine::Camera2dComponent::get_offset>("offset"_hs)
        .ctor<>();
}
