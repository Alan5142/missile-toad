# Missile Toad system registry
include_system(missile_toad/core/systems/renderer.system.hpp src/core/systems/renderer.system.cpp missiletoad::core::RendererSystem)
include_system(missile_toad/core/systems/physics.system.hpp src/core/systems/physics.system.cpp missiletoad::core::PhysicsSystem)
include_system(missile_toad/core/systems/sprite_animation.system.hpp src/core/systems/sprite_animation.system.cpp missiletoad::core::SpriteAnimationSystem)
include_system(missile_toad/core/systems/audio.system.hpp src/core/systems/audio.system.cpp missiletoad::core::AudioSystem)
include_system(missile_toad/game/systems/hub.system.hpp src/game/systems/hub.system.cpp missiletoad::game::HubSystem)
include_system(missile_toad/game/systems/laboratory.system.hpp src/game/systems/laboratory.system.cpp missiletoad::game::LaboratorySystem)
include_system(missile_toad/game/systems/menu.system.hpp src/game/systems/menu.system.cpp missiletoad::game::MenuSystem)
include_system(missile_toad/game/systems/player.system.hpp src/game/systems/player.system.cpp missiletoad::game::PlayerSystem)
