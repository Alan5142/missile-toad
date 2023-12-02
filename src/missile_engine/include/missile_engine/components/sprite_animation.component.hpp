#pragma once
#include "missile_engine/common.hpp"
#include "missile_engine/texture.hpp"
#include "missile_engine/timer.hpp"

#include <entt/meta/meta.hpp>
#include <entt/resource/resource.hpp>
#include <unordered_map>
#include <variant>

namespace missileengine
{

    /**
     * A manual transition.
     * A manual transition is a transition that is triggered by the user.
     * The user can trigger the transition by calling the should_transition method.
     */
    class SpriteAnimationTransition
    {
    public:
        /**
         * Creates a transition.
         * @param priority priority of the transition
         * @param should_transition whether the transition should transition
         */
        explicit SpriteAnimationTransition(bool should_transition);

        /**
         * Gets whether the transition should transition.
         * @return
         */
        [[nodiscard]] bool should_transition() const;

        /**
         * Sets whether the transition should transition.
         * @param should_transition whether the transition should transition
         */
        void should_transition(bool should_transition);

        /**
         * Creates an automatic transition.
         * An automatic transition is a transition that is triggered automatically when the current state is finished.
         * To achieve this, the transition flag is set to true.
         * @param next next state
         * @param priority priority of the transition
         * @return automatic transition
         */
        static SpriteAnimationTransition create_automatic()
        {
            return SpriteAnimationTransition{true};
        }

        /**
         * Creates a manual transition.
         * @param next next state
         * @param priority priority of the transition
         * @return manual transition
         */
        static SpriteAnimationTransition create_manual()
        {
            return SpriteAnimationTransition{false};
        }

    private:
        bool should_transition_{};
    };

    /**
     * Sprite animation state.
     * A sprite animation is a collection of textures that are played in order.
     * The animation can be played, stopped, looped, and the frame can be changed.
     * The animation can also be played with a timer.
     * If two or more transitions can be triggered at the same time, the transition with the highest priority will be
     * chosen.
     */
    struct SpriteAnimationState
    {
    private:
        /**
         * Frames of the animation.
         */
        std::vector<entt::resource<Texture>> frames_;

        /**
         * Transitions of the animation.
         */
        std::unordered_map<std::size_t, SpriteAnimationTransition> transitions_{};

        /**
         * Automatic transition of the animation.
         */
        Timer frame_timer_{};

        /**
         * Hash of the name of the state.
         */
        std::size_t name_hash_{};

        /**
         * Current frame of the animation.
         */
        uint32_t current_frame_{};

        /**
         * Whether the animation is playing.
         */
        bool wait_for_finish_{};

        /**
         * Whether the animation is playing.
         */
        bool is_playing_{};

        bool loop_{};

    public:
        explicit SpriteAnimationState(std::string_view name) noexcept;

        explicit SpriteAnimationState(std::size_t name_hash) noexcept;

        /**
         * Updates the animation and returns the next state if a transition is triggered.
         * If the animation is playing, it will update the current frame if the frame timer has reached 0.
         * If the animation is looping, it will reset the frame timer.
         * If the animation is not looping, it will stop the animation.
         * @param delta_time delta time since the last update
         * @return next state if a transition is triggered
         */
        std::optional<std::size_t> update(std::chrono::duration<float> delta_time) noexcept;

        /**
         * Sets the frame timer interval.
         * @param interval interval
         */
        void set_timer(Timer timer);

        [[nodiscard]] bool is_playing() const
        {
            return is_playing_;
        }

        /**
         * Adds a frame to the animation.
         * @param frame frame
         */
        void add_frame(entt::resource<Texture> frame);

        /**
         * Removes a frame from the animation.
         * @param frame frame
         */
        void remove_frame(uint32_t frame);

        /**
         * Sets the current frame of the animation.
         * @note This is implemented with modulo, so if the frame is greater than the frame count, it will wrap around.
         * @param frame frame
         */
        void set_frame(uint32_t frame);

        /**
         * Gets the current frame of the animation.
         * @return current frame of the animation
         */
        [[nodiscard]] uint32_t get_frame() const;

        /**
         * Gets the frame count of the animation.
         * @return frame count of the animation
         */
        [[nodiscard]] uint32_t get_frame_count() const;

        /**
         * Gets the current frame of the animation.
         * @return current frame of the animation
         */
        [[nodiscard]] entt::resource<Texture> get_current_frame_texture();

        /**
         * Adds a transition to the animation.
         * @param transition transition
         */
        void add_transition(std::string_view state_to, SpriteAnimationTransition transition);

        /**
         * Removes a transition from the animation.
         * @param transition transition
         */
        void remove_transition(std::string_view next);

        /**
         * Gets the transitions of the animation.
         * @return transitions of the animation
         */
        [[nodiscard]] const std::unordered_map<std::size_t, SpriteAnimationTransition> &transitions() const
        {
            return transitions_;
        }

        [[nodiscard]] SpriteAnimationTransition &get_transition(std::string_view next)
        {
            return transitions_.at(std::hash<std::string_view>{}(next));
        }

        [[nodiscard]] const SpriteAnimationTransition &get_transition(std::string_view next) const
        {
            return transitions_.at(std::hash<std::string_view>{}(next));
        }

        [[nodiscard]] SpriteAnimationTransition &get_transition(std::size_t next)
        {
            return transitions_.at(next);
        }

        [[nodiscard]] const SpriteAnimationTransition &get_transition(std::size_t next) const
        {
            return transitions_.at(next);
        }

        void play(bool play)
        {
            is_playing_ = play;
            if (play)
            {
                this->frame_timer_.start();
            }
            else
            {
                this->frame_timer_.stop();
            }
        }

        void loop(bool loop)
        {
            loop_ = loop;
        }

        /**
         * Gets the hash of the name of the state.
         * @return
         */
        [[nodiscard]] std::size_t name_hash() const
        {
            return name_hash_;
        }
    };

    /**
     * Sprite animation component.
     * It contains a runtime-defined state machine that allows the
     * transition between states.
     * A state is a collection of textures that are played in order.
     * The transitions can be set to automatic or manual.
     * There can't be more than one automatic transition.
     * If there is no automatic transition, the animation will stop when the current state is finished.
     * Unless the animation is set to loop.
     * If there is an automatic transition, the animation will transition to the next state when the current state is
     * finished.
     */
    struct SpriteAnimationComponent
    {
        static void register_component(entt::meta_ctx &ctx);

        /**
         * Adds a state to the animation.
         * @param name name of the state
         * @param state state
         * @note The name of the state must be unique as it will be used to identify the state.
         */
        void add_state(std::string_view state_to, SpriteAnimationState state);

        /**
         * Removes a state from the animation.
         * @param name name of the state
         */
        void remove_state(std::string_view name);

        /**
         * Transitions to the next state if there's any.
         * If there's no next state, it will be ignored.
         * @param name name of the state
         */
        void transition_to(std::string_view name);

        /**
         * Forces a transition to the next state.
         * It will not wait for the current state to finish.
         * @param name name of the state
         */
        void force_transition_to(std::string_view name);

        /**<<
         * Gets the current state of the animation.
         * @return current state of the animation
         */
        [[nodiscard]] SpriteAnimationState &get_state()
        {
            return states_.at(current_state_);
        }

        /**
         * Gets the current state of the animation.
         * @return current state of the animation
         */
        [[nodiscard]] const SpriteAnimationState &get_state() const
        {
            return states_.at(current_state_);
        }

        /**
         * Updates the animation.
         * @param delta_time delta time
         */
        void update(std::chrono::duration<float> delta_time) noexcept;

        [[nodiscard]] bool is_finished() const
        {
            return this->get_state().get_frame() == this->get_state().get_frame_count() - 1;
        }

        [[nodiscard]] bool is_playing() const
        {
            return this->get_state().is_playing();
        }

    private:
        /**
         * States of the animation.
         */
        std::unordered_map<std::size_t, SpriteAnimationState> states_{};

        std::size_t current_state_{};
    };
} // namespace missileengine
