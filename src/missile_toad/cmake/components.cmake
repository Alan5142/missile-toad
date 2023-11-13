# MissileToad component registration
include_component(
  missile_toad/components/player.component.hpp
  src/components/player.component.cpp missiletoad::PlayerComponent)
include_component(missile_toad/components/better_camera.component.hpp src/components/better_camera.component.cpp missiletoad::BetterCameraComponent)
include_component(missile_toad/components/turret.component.hpp src/components/turret.component.cpp missiletoad::TurretComponent)
include_component(missile_toad/components/bullet.component.hpp src/components/bullet.component.cpp missiletoad::BulletComponent)
