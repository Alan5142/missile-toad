
#include "missile_engine/components/box_collider_2d.component.hpp"
#include <box2d/b2_polygon_shape.h>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missilengine::BoxCollider2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missilengine::BoxCollider2dComponent>(ctx)
        .type("missilengine::BoxCollider2dComponent"_hs)
        .func<&missilengine::BoxCollider2dComponent::set_sensor>("set_sensor"_hs)
        .func<&missilengine::BoxCollider2dComponent::get_fixture>("get_fixture"_hs)
        .func<&missilengine::BoxCollider2dComponent::is_sensor>("is_sensor"_hs)
        .func<&missilengine::BoxCollider2dComponent::set_friction>("set_friction"_hs)
        .func<&missilengine::BoxCollider2dComponent::set_restitution>("set_restitution"_hs)
        .func<&missilengine::BoxCollider2dComponent::set_density>("set_density"_hs)
        .func<&missilengine::BoxCollider2dComponent::get_friction>("get_friction"_hs)
        .func<&missilengine::BoxCollider2dComponent::get_restitution>("get_restitution"_hs)
        .func<&missilengine::BoxCollider2dComponent::get_density>("get_density"_hs)
        .func<&missilengine::BoxCollider2dComponent::set_size>("set_size"_hs)
        .ctor<>();
}

missilengine::BoxCollider2dComponent::BoxCollider2dComponent() = default;

void missilengine::BoxCollider2dComponent::set_sensor(bool is_sensor)
{
    fixture_->SetSensor(is_sensor);
}

b2Fixture *missilengine::BoxCollider2dComponent::get_fixture() const
{
    return fixture_;
}

bool missilengine::BoxCollider2dComponent::is_sensor() const
{
    return fixture_->IsSensor();
}

void missilengine::BoxCollider2dComponent::set_friction(float friction)
{
    fixture_->SetFriction(friction);
}

void missilengine::BoxCollider2dComponent::set_restitution(float restitution)
{
    fixture_->SetRestitution(restitution);
}

void missilengine::BoxCollider2dComponent::set_density(float density)
{
    fixture_->SetDensity(density);
}

float missilengine::BoxCollider2dComponent::get_friction() const
{
    return fixture_->GetFriction();
}

float missilengine::BoxCollider2dComponent::get_restitution() const
{
    return fixture_->GetRestitution();
}

float missilengine::BoxCollider2dComponent::get_density() const
{
    return fixture_->GetDensity();
}

void missilengine::BoxCollider2dComponent::set_size(glm::vec2 size)
{
    auto *shape = dynamic_cast<b2PolygonShape *>(fixture_->GetShape());
    if (shape == nullptr)
    {
        return;
    }
    shape->SetAsBox(size.x, size.y);
}
