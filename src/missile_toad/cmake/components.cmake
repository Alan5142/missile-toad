# MissileToad component registration
include_component(
  missile_toad/components/player.component.hpp
  src/components/player.component.cpp missiletoad::PlayerComponent)
include_component(missile_toad/components/better_camera.component.hpp src/components/better_camera.component.cpp missiletoad::BetterCameraComponent)
