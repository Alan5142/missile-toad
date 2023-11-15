#include "missile_engine/components/rigidbody_2d.component.hpp"

#include <box2d/b2_world.h>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::Rigidbody2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::Rigidbody2dComponent>(ctx).type("missileengine::Rigidbody2dComponent"_hs).ctor<>();
}

void missileengine::Rigidbody2dComponent::set_linear_velocity(glm::vec2 force)
{
    body_->SetLinearVelocity({force.x, force.y});
}

void missileengine::Rigidbody2dComponent::set_static(bool is_static)
{
    body_->SetType(is_static ? b2_staticBody : b2_dynamicBody);
}
void missileengine::Rigidbody2dComponent::apply_force(glm::vec2 force, glm::vec2 point)
{
    body_->ApplyForce({force.x, force.y}, {point.x, point.y}, true);
}

void missileengine::Rigidbody2dComponent::apply_force_to_center(glm::vec2 force)
{
    body_->ApplyForceToCenter({force.x, force.y}, true);
}

void missileengine::Rigidbody2dComponent::apply_torque(float torque)
{
    body_->ApplyTorque(torque, true);
}

void missileengine::Rigidbody2dComponent::apply_linear_impulse(glm::vec2 force, glm::vec2 point)
{
    body_->ApplyLinearImpulse({force.x, force.y}, {point.x, point.y}, true);
}

void missileengine::Rigidbody2dComponent::apply_linear_impulse_to_center(glm::vec2 force)
{
    body_->ApplyLinearImpulseToCenter({force.x, force.y}, true);
}

void missileengine::Rigidbody2dComponent::set_is_bullet(bool is_bullet)
{
    body_->SetBullet(is_bullet);
}

void missileengine::Rigidbody2dComponent::set_is_fixed_rotation(bool is_fixed_rotation)
{
    body_->SetFixedRotation(is_fixed_rotation);
}

b2Body *missileengine::Rigidbody2dComponent::get_body() const
{
    return body_;
}

bool missileengine::Rigidbody2dComponent::is_static() const
{
    return body_->GetType() == b2_staticBody;
}

bool missileengine::Rigidbody2dComponent::is_dynamic() const
{
    return body_->GetType() == b2_dynamicBody;
}

glm::vec2 missileengine::Rigidbody2dComponent::get_linear_velocity() const
{
    auto velocity = body_->GetLinearVelocity();
    return {velocity.x, velocity.y};
}

float missileengine::Rigidbody2dComponent::get_angular_velocity() const
{
    return body_->GetAngularVelocity();
}

bool missileengine::Rigidbody2dComponent::is_bullet() const
{
    return body_->IsBullet();
}

bool missileengine::Rigidbody2dComponent::is_fixed_rotation() const
{
    return body_->IsFixedRotation();
}
