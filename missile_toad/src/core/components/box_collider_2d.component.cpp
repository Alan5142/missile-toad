
#include "missile_toad/core/components/box_collider_2d.component.hpp"
#include <box2d/b2_polygon_shape.h>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::BoxCollider2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::BoxCollider2dComponent>(ctx)
        .type("missiletoad::core::BoxCollider2dComponent"_hs)
        .ctor<>();
}

missiletoad::core::BoxCollider2dComponent::BoxCollider2dComponent() = default;

void missiletoad::core::BoxCollider2dComponent::set_sensor(bool is_sensor)
{
    fixture_->SetSensor(is_sensor);
}

b2Fixture *missiletoad::core::BoxCollider2dComponent::get_fixture() const
{
    return fixture_;
}

bool missiletoad::core::BoxCollider2dComponent::is_sensor() const
{
    return fixture_->IsSensor();
}

void missiletoad::core::BoxCollider2dComponent::set_friction(float friction)
{
    fixture_->SetFriction(friction);
}

void missiletoad::core::BoxCollider2dComponent::set_restitution(float restitution)
{
    fixture_->SetRestitution(restitution);
}

void missiletoad::core::BoxCollider2dComponent::set_density(float density)
{
    fixture_->SetDensity(density);
}

float missiletoad::core::BoxCollider2dComponent::get_friction() const
{
    return fixture_->GetFriction();
}

float missiletoad::core::BoxCollider2dComponent::get_restitution() const
{
    return fixture_->GetRestitution();
}

float missiletoad::core::BoxCollider2dComponent::get_density() const
{
    return fixture_->GetDensity();
}

void missiletoad::core::BoxCollider2dComponent::set_size(glm::vec2 size)
{
    auto *shape = dynamic_cast<b2PolygonShape *>(fixture_->GetShape());
    if (shape == nullptr)
    {
        return;
    }
    shape->SetAsBox(size.x, size.y);
}
