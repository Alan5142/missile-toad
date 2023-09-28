# Missile Toad system registry
include_system(missile_toad/core/systems/renderer.system.hpp src/core/systems/renderer.system.cpp missiletoad::core::RendererSystem)
include_system(missile_toad/core/systems/physics.system.hpp src/core/systems/physics.system.cpp missiletoad::core::PhysicsSystem)
include_system(missile_toad/core/systems/sprite_animation.system.hpp src/core/systems/sprite_animation.system.cpp missiletoad::core::SpriteAnimationSystem)
include_system(missile_toad/core/systems/audio.system.hpp src/core/systems/audio.system.cpp missiletoad::core::AudioSystem)
