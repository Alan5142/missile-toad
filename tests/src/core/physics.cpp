#include "missile_engine/components/box_collider_2d.component.hpp"
#include "missile_engine/components/rigidbody_2d.component.hpp"
#include "missile_engine/systems/physics.system.hpp"

#include <catch2/catch_test_macros.hpp>

#include <entt/entt.hpp>
using namespace entt::literals;

TEST_CASE("PhysicsSystem", "[core][systems]")
{
    SECTION("register_system")
    {
        entt::meta_ctx ctx;
        missilengine::PhysicsSystem::register_system(ctx);
        auto type    = entt::resolve<missilengine::PhysicsSystem>();
        auto type_id = entt::type_id<missilengine::PhysicsSystem>();
        REQUIRE(type.info() == type_id);
    }
}

TEST_CASE("BoxCollider2dComponent", "[core][components]")
{
    SECTION("register_component")
    {
        entt::meta_ctx ctx;
        missilengine::BoxCollider2dComponent::register_component(ctx);
        auto type    = entt::resolve<missilengine::BoxCollider2dComponent>();
        auto type_id = entt::type_id<missilengine::BoxCollider2dComponent>();
        REQUIRE(type.info() == type_id);
    }
}

TEST_CASE("Rigidbody2dComponent", "[core][components]")
{
    SECTION("register_component")
    {
        entt::meta_ctx ctx;
        missilengine::Rigidbody2dComponent::register_component(ctx);
        auto type    = entt::resolve<missilengine::Rigidbody2dComponent>();
        auto type_id = entt::type_id<missilengine::Rigidbody2dComponent>();
        REQUIRE(type.info() == type_id);
    }

    SECTION("Default ctor sets the body to nullptr")
    {
        missilengine::Rigidbody2dComponent rigidbody;
        REQUIRE(rigidbody.get_body() == nullptr);
    }
}
