# MissileToad component registration
include_component(
  missile_engine/components/transform.component.hpp
  src/components/transform.component.cpp missileengine::TransformComponent)
include_component(
  missile_engine/components/camera_2d.component.hpp
  src/components/camera_2d.component.cpp missileengine::Camera2dComponent)
include_component(
  missile_engine/components/sprite.component.hpp
  src/components/sprite.component.cpp missileengine::SpriteComponent)
include_component(
  missile_engine/components/rigidbody_2d.component.hpp
  src/components/rigidbody_2d.component.cpp missileengine::Rigidbody2dComponent)
include_component(
  missile_engine/components/box_collider_2d.component.hpp
  src/components/box_collider_2d.component.cpp
  missileengine::BoxCollider2dComponent)
include_component(
  missile_engine/components/sprite_animation.component.hpp
  src/components/sprite_animation.component.cpp
  missileengine::SpriteAnimationComponent)
include_component(
  missile_engine/components/audio.component.hpp
  src/components/audio.component.cpp missileengine::AudioComponent)
include_component(
  missile_engine/components/collision2d.component.hpp
  src/components/collision2d.component.cpp missileengine::Collision2dComponent)
include_component(missile_engine/components/tag.component.hpp src/components/tag.component.cpp missileengine::TagComponent)
include_component(missile_engine/components/disabled.component.hpp src/components/disabled.component.cpp missileengine::DisabledComponent)
include_component(missile_engine/components/line_renderer.component.hpp src/components/line_renderer.component.cpp missileengine::LineRendererComponent)
