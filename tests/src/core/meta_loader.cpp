#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/game.hpp"
#include "missile_toad/core/game_descriptor.hpp"

#include <catch2/catch_test_macros.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <raylib.h>

class TestSystem : public missiletoad::core::BaseSystem
{
public:
    int value = 0;

    TestSystem(missiletoad::core::Game *game)
    {
        unused(game);
    }
};

TEST_CASE("BaseSystem", "[core]")
{
    using namespace entt::literals;
    spdlog::set_level(spdlog::level::off);
    SetTraceLogLevel(LOG_NONE);

    entt::meta_ctx ctx;
    entt::meta<TestSystem>(ctx)
        .type("TestSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<missiletoad::core::Game *>();

    SECTION("Can load a type from the meta context")
    {
        spdlog::set_level(spdlog::level::off);
        auto type = entt::resolve(ctx, "TestSystem"_hs);
        REQUIRE(type.info().name() == "TestSystem");
    }

    SECTION("Can construct the type")
    {
        missiletoad::core::GameDescriptor descriptor;
        missiletoad::core::Game           game({"TEST_CASE"}, descriptor);

        auto type = entt::resolve(ctx, "TestSystem"_hs).construct(&game);

        REQUIRE(type.type().info().name() == "TestSystem");

        type.cast<TestSystem &>().value = 5;

        REQUIRE(type.cast<TestSystem &>().value == 5);
    }

    SECTION("Can cast the type to a base type")
    {
        missiletoad::core::GameDescriptor descriptor;
        missiletoad::core::Game           game({"TEST_CASE"}, descriptor);

        auto system = entt::resolve(ctx, "TestSystem"_hs).construct(&game);

        auto base_system = system.try_cast<missiletoad::core::BaseSystem>();

        REQUIRE(base_system != nullptr);
    }
}
