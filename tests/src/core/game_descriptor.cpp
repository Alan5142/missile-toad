#include "missile_engine/game_descriptor.hpp"
#include "missile_engine/schema_includes.hpp"

#include <catch2/catch_test_macros.hpp>

constexpr std::string_view GAME_DESCRIPTOR = R"({
    "name": "Missile Toad",
    "assets": [
        {
        "path": "assets",
        "mount": "assets"
        }
    ],
    "defaultScene": "scene1.json"
})";

constexpr std::string_view INVALID_GAME_DESCRIPTOR = R"({
  "name": "Missile Toad",
  "assets": [
    {
      "mount": "assets"
    }
  ],
  "preferences": [
    {
      "mount": "preferences"
    }
  ]
}
)";

TEST_CASE("GameDescriptor", "[core]")
{
    SECTION("Can load a game descriptor")
    {
        auto descriptor = missilengine::load_game_descriptor(GAME_DESCRIPTOR).value();

        REQUIRE(descriptor.name == "Missile Toad");
        REQUIRE(descriptor.assets_folders.size() == 1);
        REQUIRE(descriptor.assets_folders[0].path == "assets");
        REQUIRE(descriptor.assets_folders[0].mount_point == "assets");
    }

    SECTION("Cannot load an invalid game descriptor")
    {
        auto descriptor = missilengine::load_game_descriptor(INVALID_GAME_DESCRIPTOR);

        REQUIRE(!descriptor.has_value());
    }
}
