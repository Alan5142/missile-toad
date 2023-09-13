
#include "missile_toad/core/components/physics_2d.component.hpp"
#include <entt/locator/locator.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::Physics2dComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::Physics2dComponent>(ctx).type("missiletoad::core::Physics2dComponent"_hs).ctor<>();
}

missiletoad::core::Physics2dComponent::Physics2dComponent() : body_(nullptr), fixture_(nullptr)
{
    auto &world = entt::locator<b2World *>::value();

    b2BodyDef body_def_{};
    body_def_.type          = b2_dynamicBody;
    body_def_.enabled       = true;
    body_def_.gravityScale  = 1.0F;
    body_def_.fixedRotation = true;
    body_                   = world->CreateBody(&body_def_);
}

void missiletoad::core::Physics2dComponent::set_static(bool is_static)
{
    is_static_ = is_static;

    body_->SetType(is_static ? b2_staticBody : b2_dynamicBody);
}

void missiletoad::core::Physics2dComponent::set_collidable(bool is_collidable)
{
    if (is_collidable_ == is_collidable)
    {
        return;
    }

    is_collidable_ = is_collidable;

    if (fixture_ != nullptr && !is_collidable_)
    {
        body_->DestroyFixture(fixture_);
        fixture_ = nullptr;
    }
    else if (fixture_ == nullptr && is_collidable_)
    {
        b2FixtureDef fixture_def{};
        fixture_def.density     = 1.0F;
        fixture_def.friction    = 0.3F;
        fixture_def.restitution = 0.5F;
        // Only box colliders for now.
        b2PolygonShape shape_{};
        shape_.SetAsBox(1.0F, 1.0F);
        fixture_def.shape            = &shape_;
        fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
        fixture_                     = body_->CreateFixture(&fixture_def);
    }
}
void missiletoad::core::Physics2dComponent::apply_force(float x, float y)
{
    body_->ApplyForceToCenter({x, y}, true);
}
void missiletoad::core::Physics2dComponent::set_position(float x, float y)
{
    body_->SetTransform({x, y}, body_->GetAngle());
}
void missiletoad::core::Physics2dComponent::set_linear_velocity(float x, float y)
{
    body_->SetLinearVelocity({x, y});
}
