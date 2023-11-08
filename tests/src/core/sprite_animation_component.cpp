#include <catch2/catch_test_macros.hpp>

#include <missile_engine/components/sprite_animation.component.hpp>

TEST_CASE("SpriteAnimationTransition", "[core][sprite-animation]")
{
    SECTION("create_automatic")
    {
        auto transition = missileengine::SpriteAnimationTransition::create_automatic();
        REQUIRE(transition.should_transition());
    }

    SECTION("create_manual")
    {
        auto transition = missileengine::SpriteAnimationTransition::create_manual();
        REQUIRE(!transition.should_transition());
    }

    SECTION("Can set if the transition should happen")
    {
        auto transition = missileengine::SpriteAnimationTransition::create_manual();
        transition.should_transition(true);
        REQUIRE(transition.should_transition());
    }
}

TEST_CASE("SpriteAnimationState", "[core][sprite-animation]")
{
    SECTION("Can create a state")
    {
        missileengine::SpriteAnimationState state("test");

        REQUIRE(state.name_hash() == std::hash<std::string_view>{}("test"));
    }

    SECTION("Can add frames")
    {
        std::array<entt::resource<missileengine::Texture>, 3> textures = {
            entt::resource<missileengine::Texture>(std::make_shared<missileengine::Texture>()),
            entt::resource<missileengine::Texture>(std::make_shared<missileengine::Texture>()),
            entt::resource<missileengine::Texture>(std::make_shared<missileengine::Texture>()),
        };
        missileengine::SpriteAnimationState state("test");

        state.add_frame(textures[0]);
        state.add_frame(textures[1]);
        state.add_frame(textures[2]);

        REQUIRE(state.get_frame_count() == 3);
        REQUIRE(state.get_frame() == 0);
    }

    SECTION("Can update the frames with a timer")
    {
        using namespace std::chrono_literals;
        std::array<entt::resource<missileengine::Texture>, 3> textures = {
            entt::resource<missileengine::Texture>(std::make_shared<missileengine::Texture>()),
            entt::resource<missileengine::Texture>(std::make_shared<missileengine::Texture>()),
            entt::resource<missileengine::Texture>(std::make_shared<missileengine::Texture>()),
        };
        missileengine::SpriteAnimationState state("test");

        state.add_frame(textures[0]);
        state.add_frame(textures[1]);
        state.add_frame(textures[2]);

        state.set_timer(missileengine::TimerBuilder().with_interval(0.2s).build());
        state.play(true);

        REQUIRE(state.get_frame() == 0);

        state.update(1s);

        REQUIRE(state.get_frame() == 1);

        state.update(1s);

        REQUIRE(state.get_frame() == 2);

        state.update(1s);

        REQUIRE(state.get_frame() == 0);
    }

    SECTION("Can have transitions")
    {
        missileengine::SpriteAnimationState      state("test");
        missileengine::SpriteAnimationTransition transition =
            missileengine::SpriteAnimationTransition::create_automatic();
        missileengine::SpriteAnimationTransition transition2 =
            missileengine::SpriteAnimationTransition::create_automatic();

        state.add_transition("transition2", transition);
        state.add_transition("transition", transition2);

        REQUIRE(state.transitions().size() == 2);
    }

    SECTION("Transitions update based on input")
    {
        using namespace std::chrono_literals;

        auto frame = entt::resource<missileengine::Texture>(std::make_shared<missileengine::Texture>());

        missileengine::SpriteAnimationState state("test");
        missileengine::SpriteAnimationState state2("test2");

        state.add_frame(frame);

        missileengine::SpriteAnimationTransition transition =
            missileengine::SpriteAnimationTransition::create_automatic();
        missileengine::SpriteAnimationTransition transition2 =
            missileengine::SpriteAnimationTransition::create_automatic();

        state.add_transition("test2", transition);

        state2.add_transition("test", transition2);

        state.play(true);

        REQUIRE(state.transitions().size() == 1);

        // When playing, the transition should be true, so the next state should be "test2".

        auto next_state = state.update(1s);

        REQUIRE(next_state == std::hash<std::string_view>{}("test2"));
    }
}

TEST_CASE("SpriteAnimationComponent", "[core][sprite-animation]")
{
    SECTION("Can create a sprite animation component")
    {
        missileengine::SpriteAnimationComponent component;

        REQUIRE(true);
    }

    SECTION("Can add states")
    {
        missileengine::SpriteAnimationComponent component;

        auto animation_state1 = missileengine::SpriteAnimationState("test");
        auto animation_state2 = missileengine::SpriteAnimationState("test2");

        component.add_state("test", animation_state1);
        component.add_state("test2", animation_state2);

        component.force_transition_to("test");

        REQUIRE(component.get_state().name_hash() == std::hash<std::string_view>{}("test"));
    }

    SECTION("Can transition")
    {
        using namespace std::chrono_literals;
        missileengine::SpriteAnimationComponent component;

        auto frame = entt::resource<missileengine::Texture>(std::make_shared<missileengine::Texture>());

        auto animation_state1 = missileengine::SpriteAnimationState("test");
        animation_state1.add_frame(frame);
        auto animation_state2 = missileengine::SpriteAnimationState("test2");

        auto transition1 = missileengine::SpriteAnimationTransition::create_automatic();
        animation_state1.add_transition("test2", transition1);

        animation_state1.play(true);
        animation_state2.play(true);

        component.add_state("test", animation_state1);
        component.add_state("test2", animation_state2);

        component.force_transition_to("test");

        REQUIRE(component.get_state().name_hash() == std::hash<std::string_view>{}("test"));

        component.transition_to("test2");

        component.update(1s);

        REQUIRE(component.get_state().name_hash() == std::hash<std::string_view>{}("test2"));
    }
}
