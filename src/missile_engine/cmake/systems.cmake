# Missile Toad system registry
include_system(missile_engine/systems/renderer.system.hpp
               src/systems/renderer.system.cpp missileengine::RendererSystem)
include_system(missile_engine/systems/physics.system.hpp
               src/systems/physics.system.cpp missileengine::PhysicsSystem)
include_system(
  missile_engine/systems/sprite_animation.system.hpp
  src/systems/sprite_animation.system.cpp missileengine::SpriteAnimationSystem)
include_system(missile_engine/systems/audio.system.hpp
               src/systems/audio.system.cpp missileengine::AudioSystem)
