#include "missile_engine/locator.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Locator", "[core]")
{
    missilengine::Locator locator;
    SECTION("Locator has an empty service map on construction")
    {
        REQUIRE(locator.size() == 0);
    }

    SECTION("Can insert anything in the container")
    {
        locator.emplace<int>(5);

        REQUIRE(locator.size() == 1);
    }

    SECTION("Const and pointer qualifiers are preserved")
    {
        int a = 10;
        locator.emplace<const int>(5);
        locator.emplace<int *>(&a);

        REQUIRE(locator.size() == 2);
    }

    SECTION("Getting a service that doesn't exist returns an empty optional")
    {
        REQUIRE(locator.get<int>().has_value() == false);
    }

    SECTION("Can get a service from the container")
    {
        REQUIRE(locator.emplace<int>(5) == true);

        REQUIRE(locator.get<int>() == 5);
    }

    SECTION("Cannot insert multiple services of the same type without a name")
    {
        REQUIRE(locator.emplace<int>(5) == true);
        REQUIRE(locator.emplace<int>(5) == false);
    }

    SECTION("Can insert multiple services of the same type with a name")
    {
        REQUIRE(locator.emplace_named<int>("int1", 5) == true);
        REQUIRE(locator.emplace_named<int>("int2", 5) == true);
    }

    SECTION("Can get a service from the container by name")
    {
        REQUIRE(locator.emplace_named<int>("int1", 5) == true);
        REQUIRE(locator.emplace_named<int>("int2", 10) == true);

        REQUIRE(locator.get<int>("int1") == 5);
        REQUIRE(locator.get<int>("int2") == 10);
    }

    SECTION("Cannot get a service from the container by name if it doesn't exist")
    {
        REQUIRE(locator.emplace_named<int>("int1", 5) == true);
        REQUIRE(locator.emplace_named<int>("int2", 10) == true);

        REQUIRE(locator.get<int>("int3").has_value() == false);
    }

    SECTION("Supports insertion of multiple types")
    {
        REQUIRE(locator.emplace<int>(5) == true);
        REQUIRE(locator.emplace<float>(5.0f) == true);
        REQUIRE(locator.emplace<std::string>("Hello") == true);

        REQUIRE(locator.get<int>().value() == 5);
        REQUIRE(locator.get<float>().value() == 5.0f);
        REQUIRE(locator.get<std::string>().value().get() == "Hello");
    }

    SECTION("Supports erasure of services")
    {
        REQUIRE(locator.emplace<int>(5) == true);
        REQUIRE(locator.emplace<float>(5.0f) == true);
        REQUIRE(locator.size() == 2);

        locator.erase<int>();
        REQUIRE(locator.size() == 1);
    }

    SECTION("All services are erased when clear is called")
    {
        REQUIRE(locator.emplace<int>(5) == true);
        REQUIRE(locator.emplace<float>(5.0f) == true);
        REQUIRE(locator.size() == 2);

        locator.clear();
        REQUIRE(locator.size() == 0);
    }
}
