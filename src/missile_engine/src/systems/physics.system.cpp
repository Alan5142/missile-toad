
#include "missile_engine/systems/physics.system.hpp"
#include "missile_engine/components/box_collider_2d.component.hpp"
#include "missile_engine/components/collision2d.component.hpp"
#include "missile_engine/components/disabled.component.hpp"
#include "missile_engine/components/rigidbody_2d.component.hpp"
#include "missile_engine/components/sprite.component.hpp"
#include "missile_engine/components/transform.component.hpp"
#include "missile_engine/game.hpp"

#include <algorithm>
#include <box2d/b2_contact.h>
#include <entt/entity/registry.hpp>
#include <entt/meta/factory.hpp>
#include <glm/trigonometric.hpp>

constexpr auto DEFAULT_DENSITY     = 1.0F;
constexpr auto DEFAULT_FRICTION    = 0.3F;
constexpr auto DEFAULT_RESTITUTION = 0.5F;

constexpr auto VELOCITY_ITERATIONS = 6;
constexpr auto POSITION_ITERATIONS = 2;

class ContactListener : public b2ContactListener
{
    missileengine::Game *game_{};

public:
    ContactListener(missileengine::Game *game) : game_(game)
    {
    }

    ~ContactListener() override = default;

    ContactListener(const ContactListener &) = default;

    ContactListener(ContactListener &&) noexcept = default;

    ContactListener &operator=(const ContactListener &) = default;

    ContactListener &operator=(ContactListener &&) noexcept = default;

    void BeginContact(b2Contact *contact) override
    {
        handle_contact(contact, missileengine::ECollisionStatus::ENTER);
    }

    void EndContact(b2Contact *contact) override
    {
        handle_contact(contact, missileengine::ECollisionStatus::EXIT);
    }

private:
    void handle_contact(b2Contact *contact, missileengine::ECollisionStatus status)
    {
        auto *fixture_a = contact->GetFixtureA();
        auto *fixture_b = contact->GetFixtureB();

        // NOLINTNEXTLINE
        auto entity_a = static_cast<entt::entity>(fixture_a->GetUserData().pointer);
        // NOLINTNEXTLINE
        auto entity_b = static_cast<entt::entity>(fixture_b->GetUserData().pointer);

        auto &registry = game_->active_scene().get_registry();

        auto *collision_a = registry.try_get<missileengine::Collision2dComponent>(entity_a);
        auto *collision_b = registry.try_get<missileengine::Collision2dComponent>(entity_b);

        if (collision_a != nullptr)
        {
            collision_a->callback(entity_a, entity_b, status);
        }
        if (collision_b != nullptr)
        {
            collision_b->callback(entity_b, entity_a, status);
        }
    }
};

void missileengine::PhysicsSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::PhysicsSystem>(ctx)
        .type("missileengine::PhysicsSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
}

missileengine::PhysicsSystem::PhysicsSystem(missileengine::Game *game)
    : world_(&game->active_scene().physics_world_), registry_(&game->active_scene().get_registry())
{
    static auto contact_listener = ContactListener{game};
    world_->SetContactListener(&contact_listener);
    transform_observer_.connect(*registry_,
                                entt::collector
                                    .update<missileengine::TransformComponent>() //
                                    .where<missileengine::BoxCollider2dComponent>());

    registry_->on_construct<BoxCollider2dComponent>().connect<&PhysicsSystem::on_box_collider_created>(this);
    registry_->on_construct<Rigidbody2dComponent>().connect<&PhysicsSystem::on_rigidbody_created>(this);

    registry_->on_construct<DisabledComponent>().connect<&PhysicsSystem::on_entity_disabled>(this);
    registry_->on_destroy<DisabledComponent>().connect<&PhysicsSystem::on_entity_enabled>(this);
}

missileengine::PhysicsSystem::~PhysicsSystem()
{
    registry_->on_construct<BoxCollider2dComponent>().disconnect<&PhysicsSystem::on_box_collider_created>(this);
    registry_->on_construct<Rigidbody2dComponent>().disconnect<&PhysicsSystem::on_rigidbody_created>(this);
}

void missileengine::PhysicsSystem::on_fixed_update(float delta_time)
{
    // First, we need to update the physics bodies with the transform. This just in case the transform was updated
    auto rigidbody_view =
        registry_->view<Rigidbody2dComponent, TransformComponent>(entt::exclude<missileengine::DisabledComponent>);
    std::for_each(
        rigidbody_view.begin(), rigidbody_view.end(),
        [&](auto entity)
        {
            auto &physics   = registry_->get<missileengine::Rigidbody2dComponent>(entity);
            auto &transform = registry_->get<missileengine::TransformComponent>(entity);

            auto *body = physics.get_body();

            body->SetTransform({transform.position.x, transform.position.y}, glm::radians(transform.rotation));

            // Also update the size of the box collider if it contains a box collider.
            auto *sprite       = registry_->try_get<missileengine::SpriteComponent>(entity);
            auto *box_collider = registry_->try_get<missileengine::BoxCollider2dComponent>(entity);
            if (sprite != nullptr && box_collider != nullptr)
            {
                const auto &texture = sprite->texture->get_texture();
                if (sprite->scissors != std::nullopt)
                {
                    box_collider->set_size(transform.scale * PHYSICS_SCALE);
                }
                else
                {
                    const auto scale_x = (static_cast<float>(texture.width) / PIXELS_PER_UNIT) * transform.scale.x;
                    const auto scale_y = (static_cast<float>(texture.height) / PIXELS_PER_UNIT) * transform.scale.y;
                    box_collider->set_size({scale_x * PHYSICS_SCALE, scale_y * PHYSICS_SCALE});
                }
            }
        });

    // Update the physics bodies
    world_->Step(delta_time, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

    // After updating the physics bodies, we need to update the transforms with the physics bodies.
    std::for_each(rigidbody_view.begin(), rigidbody_view.end(),
                  [&](auto entity)
                  {
                      auto &rigidbody = registry_->get<missileengine::Rigidbody2dComponent>(entity);
                      auto &transform = registry_->get<missileengine::TransformComponent>(entity);
                      auto *body      = rigidbody.get_body();
                      auto  position  = body->GetPosition();

                      // Only update the transform if the physics body is not static and the transform has changed.
                      // Static bodies are not affected by physics, so we don't need to update the transform.
                      if (rigidbody.is_static() || transform.position == glm::vec2{position.x, position.y})
                      {
                          return;
                      }

                      transform.position.x = position.x;
                      transform.position.y = position.y;
                      transform.rotation   = glm::degrees(body->GetAngle());

                      registry_->patch<TransformComponent>(entity);
                  });
}

void missileengine::PhysicsSystem::on_box_collider_created(entt::registry &registry, entt::entity entity)
{
    // Only use box collider and rigidbody components.
    auto &transform    = registry.get_or_emplace<TransformComponent>(entity);
    auto &box_collider = registry.get_or_emplace<BoxCollider2dComponent>(entity);
    auto &rigidbody    = registry.get_or_emplace<Rigidbody2dComponent>(entity);

    auto fixture_def        = b2FixtureDef{};
    fixture_def.density     = DEFAULT_DENSITY;
    fixture_def.friction    = DEFAULT_FRICTION;
    fixture_def.restitution = DEFAULT_RESTITUTION;
    // Only box colliders for now.
    auto shape = b2PolygonShape{};
    shape.SetAsBox(transform.scale.x * PHYSICS_SCALE, transform.scale.y * PHYSICS_SCALE);

    fixture_def.shape            = &shape;
    fixture_def.userData.pointer = static_cast<uintptr_t>(entity);
    box_collider.fixture_        = rigidbody.body_->CreateFixture(&fixture_def);
}

void missileengine::PhysicsSystem::on_rigidbody_created(entt::registry &registry, entt::entity entity)
{
    // Get transform
    auto &transform = registry.get_or_emplace<TransformComponent>(entity);

    // Create rigidbody
    auto &rigidbody = registry.get_or_emplace<Rigidbody2dComponent>(entity);

    auto body_def = b2BodyDef{};
    body_def.type = b2_staticBody;
    body_def.position.Set(transform.position.x, transform.position.y);
    body_def.fixedRotation = true;
    body_def.angle         = glm::radians(transform.rotation);
    body_def.enabled       = true;
    rigidbody.body_        = world_->CreateBody(&body_def);
}

void missileengine::PhysicsSystem::on_entity_disabled(entt::registry &registry, entt::entity entity)
{
    auto *rigidbody = registry.try_get<Rigidbody2dComponent>(entity);
    if (rigidbody != nullptr)
    {
        rigidbody->body_->SetEnabled(false);
    }
}

void missileengine::PhysicsSystem::on_entity_enabled(entt::registry &registry, entt::entity entity)
{
    auto *rigidbody = registry.try_get<Rigidbody2dComponent>(entity);
    if (rigidbody != nullptr)
    {
        rigidbody->body_->SetEnabled(true);
    }
}
