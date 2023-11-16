
#include "missile_engine/components/circle_collider_2d.component.hpp"

#include <box2d/b2_circle_shape.h>
#include <entt/meta/factory.hpp>

void missileengine::CircleCollider2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::CircleCollider2dComponent>(ctx)
        .type("missileengine::CircleCollider2dComponent"_hs)
        .ctor<>();
}

missileengine::CircleCollider2dComponent::CircleCollider2dComponent() = default;

void missileengine::CircleCollider2dComponent::set_sensor(bool is_sensor)
{
    fixture_->SetSensor(is_sensor);
}

void missileengine::CircleCollider2dComponent::set_friction(float friction)
{
    fixture_->SetFriction(friction);
}

void missileengine::CircleCollider2dComponent::set_restitution(float restitution)
{
    fixture_->SetRestitution(restitution);
}

void missileengine::CircleCollider2dComponent::set_density(float density)
{
    fixture_->SetDensity(density);
}

void missileengine::CircleCollider2dComponent::set_size(float radius)
{
    auto *shape = dynamic_cast<b2CircleShape *>(fixture_->GetShape());
    if (shape == nullptr)
    {
        throw std::runtime_error("Shape is not a circle");
    }
    shape->m_radius = radius;
}

b2Fixture *missileengine::CircleCollider2dComponent::get_fixture() const
{
    return fixture_;
}

bool missileengine::CircleCollider2dComponent::is_sensor() const
{
    return fixture_->IsSensor();
}

float missileengine::CircleCollider2dComponent::get_friction() const
{
    return fixture_->GetFriction();
}

float missileengine::CircleCollider2dComponent::get_restitution() const
{
    return fixture_->GetRestitution();
}

float missileengine::CircleCollider2dComponent::get_density() const
{
    return fixture_->GetDensity();
}
