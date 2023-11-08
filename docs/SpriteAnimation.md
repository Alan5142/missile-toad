# Sprite animation

## Introduction

The `SpriteAnimationComponent` is composed of 3 parts:
* `SpriteAnimationComponent` - the component itself, it stores states (animations) and the current state
* `SpriteAnimationState` - a state (animation) of the component, it stores frames and the current frame as well as the transition list.
* `SpriteAnimationTransition` - a transition between states, it stores the target state and the condition to trigger the transition.

## Usage

First, you need to create a `SpriteAnimationComponent` and add it to the entity.

Then you can attach a set of states to the component and transitions to the states.

```cpp

auto run_texture_1 = asset_manager.load<missileengine::Texture>("run_1.png");
auto run_texture_2 = asset_manager.load<missileengine::Texture>("run_2.png");
auto run_texture_3 = asset_manager.load<missileengine::Texture>("run_3.png");

auto idle_texture_1 = asset_manager.load<missileengine::Texture>("idle_1.png");
auto idle_texture_2 = asset_manager.load<missileengine::Texture>("idle_2.png");
auto idle_texture_3 = asset_manager.load<missileengine::Texture>("idle_3.png");

scene.create_entity()
        .with_component_using_function<missileengine::SpriteAnimationComponent>([&](auto &sprite_animation)
        {
            auto run_state = missileengine::SpriteAnimationState("run");
            run_state.add_frame(run_texture_1);
            run_state.add_frame(run_texture_2);
            run_state.add_frame(run_texture_3);
            run_state.play(true); // Play the animation
            run_state.loop(true); // Loop the animation until a transition is triggered or the animation is stopped

            auto idle_state = missileengine::SpriteAnimationState("idle");
            idle_state.add_frame(idle_texture_1);
            idle_state.add_frame(idle_texture_2);
            idle_state.add_frame(idle_texture_3);
            idle_state.play(true);
            idle_state.loop(true);

            auto run_to_idle_transition = missileengine::SpriteAnimationTransition::create_manual();
            run_state.add_transition("idle", run_to_idle_transition); // Must match the state name

            auto idle_to_run_transition = missileengine::SpriteAnimationTransition::create_manual();
            idle_state.add_transition("run", idle_to_run_transition); // Must match the state name

            sprite_animation.add_state(run_state);
            sprite_animation.add_state(idle_state);
        })
        .build();
```

And to trigger a transition, you can do:

```cpp
auto view = scene.view<missileengine::SpriteAnimationComponent>();

for (auto entity : view)
{
    auto &sprite_animation = view.get(entity);
    sprite_animation.transition_to("run"); // Waits for the current animation to finish
    sprite_animation.force_transition_to("run"); // Force the transition, the current animation is stopped and the new one is played
}
```
