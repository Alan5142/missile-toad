#include "missile_toad/core/components/box_collider_2d.component.hpp"
#include "missile_toad/core/components/rigidbody_2d.component.hpp"
#include "missile_toad/core/systems/physics.system.hpp"

#include <catch2/catch_test_macros.hpp>

#include <entt/entt.hpp>
using namespace entt::literals;

TEST_CASE("PhysicsSystem", "[core][systems]")
{
    SECTION("register_system")
    {
        entt::meta_ctx ctx;
        missileenginecore::PhysicsSystem::register_system(ctx);
        auto type    = entt::resolve<missileenginecore::PhysicsSystem>();
        auto type_id = entt::type_id<missileenginecore::PhysicsSystem>();
        REQUIRE(type.info() == type_id);
    }
}

TEST_CASE("BoxCollider2dComponent", "[core][components]")
{
    SECTION("register_component")
    {
        entt::meta_ctx ctx;
        missileenginecore::BoxCollider2dComponent::register_component(ctx);
        auto type    = entt::resolve<missileenginecore::BoxCollider2dComponent>();
        auto type_id = entt::type_id<missileenginecore::BoxCollider2dComponent>();
        REQUIRE(type.info() == type_id);
    }
}

TEST_CASE("Rigidbody2dComponent", "[core][components]")
{
    SECTION("register_component")
    {
        entt::meta_ctx ctx;
        missileenginecore::Rigidbody2dComponent::register_component(ctx);
        auto type    = entt::resolve<missileenginecore::Rigidbody2dComponent>();
        auto type_id = entt::type_id<missileenginecore::Rigidbody2dComponent>();
        REQUIRE(type.info() == type_id);
    }

    SECTION("Default ctor sets the body to nullptr")
    {
        missileenginecore::Rigidbody2dComponent rigidbody;
        REQUIRE(rigidbody.get_body() == nullptr);
    }
}
