
#include "missile_toad/core/systems/physics.system.hpp"
#include "missile_toad/core/components/box_collider_2d.component.hpp"
#include "missile_toad/core/components/rigidbody_2d.component.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include "missile_toad/core/locator.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <glm/trigonometric.hpp>

void missiletoad::core::PhysicsSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::PhysicsSystem>(ctx)
        .type("missiletoad::core::PhysicsSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<>();
}

missiletoad::core::PhysicsSystem::PhysicsSystem(missiletoad::core::Locator &locator) : world_({0, 0})
{
    locator.emplace<PhysicsSystem *>(this);
    auto registry_opt = locator.get<entt::registry *>();
    if (!registry_opt.has_value())
    {
        throw std::runtime_error("PhysicsSystem requires an entt::registry to be in the locator.");
    }
    registry_ = registry_opt.value();

    transform_observer_.connect(*registry_,
                                entt::collector
                                    .update<missiletoad::core::Rigidbody2dComponent>() //
                                    .where<missiletoad::core::TransformComponent>());

    registry_->on_construct<core::BoxCollider2dComponent>().connect<&PhysicsSystem::on_box_collider_created>(this);
    registry_->on_construct<core::Rigidbody2dComponent>().connect<&PhysicsSystem::on_rigidbody_created>(this);
}

void missiletoad::core::PhysicsSystem::on_fixed_update(float delta_time)
{
    // First, we need to update the physics bodies with the transform. This just in case the transform was updated
    for (const auto entity : transform_observer_)
    {
        auto &physics   = registry_->get<missiletoad::core::Rigidbody2dComponent>(entity);
        auto &transform = registry_->get<missiletoad::core::TransformComponent>(entity);

        auto *body = physics.get_body();

        body->SetTransform({transform.position.x, transform.position.y}, glm::radians(transform.rotation));

        // Also update the size of the box collider if it contains a box collider.
        if (auto *box_collider = registry_->try_get<missiletoad::core::BoxCollider2dComponent>(entity);
            box_collider != nullptr)
        {
            box_collider->set_size(transform.scale);
        }
    }

    // Update the physics bodies
    world_.Step(delta_time, 6, 2);

    // After updating the physics bodies, we need to update the transforms with the physics bodies.
    for (auto entity : registry_->view<core::Rigidbody2dComponent, core::TransformComponent>())
    {
        auto &rigidbody = registry_->get<missiletoad::core::Rigidbody2dComponent>(entity);
        auto &transform = registry_->get<missiletoad::core::TransformComponent>(entity);
        auto *body      = rigidbody.get_body();
        auto  position  = body->GetPosition();

        // Only update the transform if the physics body is not static and the transform has changed.
        // Static bodies are not affected by physics, so we don't need to update the transform.
        if (rigidbody.is_static() || transform.position == glm::vec2{position.x, position.y})
        {
            continue;
        }

        transform.position.x = position.x;
        transform.position.y = position.y;
        transform.rotation   = glm::degrees(body->GetAngle());

        registry_->patch<core::TransformComponent>(entity);
    }
}

void missiletoad::core::PhysicsSystem::on_box_collider_created(entt::registry &registry, entt::entity entity)
{
    // Only use box collider and rigidbody components.
    auto &transform    = registry.get<core::TransformComponent>(entity);
    auto &box_collider = registry.get<core::BoxCollider2dComponent>(entity);
    auto &rigidbody    = registry.get_or_emplace<core::Rigidbody2dComponent>(entity);

    auto fixture_def        = b2FixtureDef{};
    fixture_def.density     = 1.0F;
    fixture_def.friction    = 0.3F;
    fixture_def.restitution = 0.5F;
    // Only box colliders for now.
    auto shape = b2PolygonShape{};
    shape.SetAsBox(transform.scale.x, transform.scale.y);

    fixture_def.shape            = &shape;
    fixture_def.userData.pointer = static_cast<uintptr_t>(entity);
    box_collider.fixture_        = rigidbody.body_->CreateFixture(&fixture_def);
}

void missiletoad::core::PhysicsSystem::on_rigidbody_created(entt::registry &registry, entt::entity entity)
{
    // Get transform
    auto &transform = registry.get_or_emplace<core::TransformComponent>(entity);

    // Create rigidbody
    auto &rigidbody = registry.get<core::Rigidbody2dComponent>(entity);

    auto body_def = b2BodyDef{};
    body_def.type = b2_staticBody;
    body_def.position.Set(transform.position.x, transform.position.y);
    body_def.fixedRotation = true;
    body_def.angle         = glm::radians(transform.rotation);
    body_def.enabled       = true;
    rigidbody.body_        = world_.CreateBody(&body_def);
}
