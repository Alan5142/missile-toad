# Missile Toad system registry
include_system(missile_engine/systems/renderer.system.hpp
               src/systems/renderer.system.cpp missilengine::RendererSystem)
include_system(missile_engine/systems/physics.system.hpp
               src/systems/physics.system.cpp missilengine::PhysicsSystem)
include_system(
  missile_engine/systems/sprite_animation.system.hpp
  src/systems/sprite_animation.system.cpp missilengine::SpriteAnimationSystem)
include_system(missile_engine/systems/audio.system.hpp
               src/systems/audio.system.cpp missilengine::AudioSystem)
