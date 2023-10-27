#include "missile_engine/base_system.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/game_descriptor.hpp"

#include <catch2/catch_test_macros.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <raylib.h>

class TestSystem : public missilengine::BaseSystem
{
public:
    int value = 0;

    TestSystem(missilengine::Game *game)
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
    entt::meta<TestSystem>(ctx).type("TestSystem"_hs).base<missilengine::BaseSystem>().ctor<missilengine::Game *>();

    SECTION("Can load a type from the meta context")
    {
        spdlog::set_level(spdlog::level::off);
        auto type                 = entt::resolve(ctx, "TestSystem"_hs);
        auto contains_base_system = type.info().name().find("TestSystem") != std::string::npos;
        REQUIRE(contains_base_system);
    }

    SECTION("Can construct the type")
    {
        missilengine::GameDescriptor descriptor;
        missilengine::Game           game({"TEST_CASE"}, descriptor);

        auto type = entt::resolve(ctx, "TestSystem"_hs).construct(&game);

        type.cast<TestSystem &>().value = 5;

        REQUIRE(type.cast<TestSystem &>().value == 5);
    }

    SECTION("Can cast the type to a base type")
    {
        missilengine::GameDescriptor descriptor;
        missilengine::Game           game({"TEST_CASE"}, descriptor);

        auto system = entt::resolve(ctx, "TestSystem"_hs).construct(&game);

        auto base_system = system.try_cast<missilengine::BaseSystem>();

        REQUIRE(base_system != nullptr);
    }
}
