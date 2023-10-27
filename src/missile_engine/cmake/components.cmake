# MissileToad component registration
include_component(
  missile_engine/components/transform.component.hpp
  src/components/transform.component.cpp missilengine::TransformComponent)
include_component(
  missile_engine/components/camera_2d.component.hpp
  src/components/camera_2d.component.cpp missilengine::Camera2dComponent)
include_component(
  missile_engine/components/sprite.component.hpp
  src/components/sprite.component.cpp missilengine::SpriteComponent)
include_component(
  missile_engine/components/rigidbody_2d.component.hpp
  src/components/rigidbody_2d.component.cpp missilengine::Rigidbody2dComponent)
include_component(
  missile_engine/components/box_collider_2d.component.hpp
  src/components/box_collider_2d.component.cpp
  missilengine::BoxCollider2dComponent)
include_component(
  missile_engine/components/sprite_animation.component.hpp
  src/components/sprite_animation.component.cpp
  missilengine::SpriteAnimationComponent)
include_component(
  missile_engine/components/audio.component.hpp
  src/components/audio.component.cpp missilengine::AudioComponent)
include_component(
  missile_engine/components/collision2d.component.hpp
  src/components/collision2d.component.cpp missilengine::Collision2dComponent)
