# Missile Toad system registry
include_system(missile_toad/systems/hub.system.hpp src/systems/hub.system.cpp
               missiletoad::HubSystem)
include_system(missile_toad/systems/laboratory.system.hpp
               src/systems/laboratory.system.cpp missiletoad::LaboratorySystem)
include_system(missile_toad/systems/menu.system.hpp src/systems/menu.system.cpp
               missiletoad::MenuSystem)
include_system(missile_toad/systems/player.system.hpp
               src/systems/player.system.cpp missiletoad::PlayerSystem)
include_system(missile_toad/systems/camera.system.hpp src/systems/camera.system.cpp missiletoad::CameraSystem)
include_system(missile_toad/systems/enemy.system.hpp src/systems/enemy.system.cpp missiletoad::EnemySystem)
include_system(missile_toad/systems/health.system.hpp src/systems/health.system.cpp missiletoad::HealthSystem)
