
#include "missile_toad/core/systems/physics.system.hpp"
#include "missile_toad/core/components/physics_2d.component.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include <entt/entity/registry.hpp>
#include <entt/locator/locator.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <raylib.h>

void missiletoad::core::PhysicsSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::PhysicsSystem>(ctx)
        .type("missiletoad::core::PhysicsSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<>();
}

missiletoad::core::PhysicsSystem::PhysicsSystem() : world_(b2Vec2(0.0F, 0.0F))
{
    entt::locator<b2World *>::emplace(&world_);
    auto &registry = *entt::locator<entt::registry *>::value();
    transform_observer_.connect(registry,
                                entt::collector
                                    .update<missiletoad::core::Physics2dComponent>() //
                                    .where<missiletoad::core::TransformComponent>());
}

void missiletoad::core::PhysicsSystem::on_fixed_update(float delta_time)
{
    auto &registry = *entt::locator<entt::registry *>::value();

    // First, we need to update the physics bodies with the transform. This just in case the transform was updated
    transform_observer_.each(
        [&](const auto entity)
        {
            auto &physics   = registry.get<missiletoad::core::Physics2dComponent>(entity);
            auto &transform = registry.get<missiletoad::core::TransformComponent>(entity);

            auto *body = physics.get_body();

            body->SetTransform({transform.position.x, transform.position.y}, transform.rotation);
        });

    // Update the physics bodies
    world_.Step(delta_time, 6, 2);

    // After updating the physics bodies, we need to update the transforms with the physics bodies.
    for (auto entity : registry.view<core::Physics2dComponent, core::TransformComponent>())
    {
        auto &physics   = registry.get<missiletoad::core::Physics2dComponent>(entity);
        auto &transform = registry.get<missiletoad::core::TransformComponent>(entity);
        auto *body      = physics.get_body();
        auto  position  = body->GetPosition();

        // Only update the transform if the physics body is not static and the transform has changed.
        // Static bodies are not affected by physics, so we don't need to update the transform.
        if (physics.is_static() || transform.position == glm::vec2{position.x, position.y})
        {
            continue;
        }

        registry.patch<core::TransformComponent>(entity,
                                                 [&](auto &transform_component)
                                                 {
                                                     transform_component.position.x = position.x;
                                                     transform_component.position.y = position.y;
                                                     transform_component.rotation   = body->GetAngle();
                                                 });
    }
}
