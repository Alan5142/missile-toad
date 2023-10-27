#pragma once
#include "missile_engine/common.hpp"
#include "missile_engine/texture.hpp"
#include "missile_engine/timer.hpp"

#include <entt/meta/meta.hpp>
#include <entt/resource/resource.hpp>

namespace missilengine
{
    struct SpriteAnimationComponent
    {
    private:
        std::vector<entt::resource<Texture>> frames_;
        Timer                                frame_timer_{};
        uint32_t                             current_frame_{};

    public:
        // NOLINTNEXTLINE(*-non-private-member-variables-in-classes)
        bool is_playing{};
        // NOLINTNEXTLINE(*-non-private-member-variables-in-classes)
        bool loop{};

        static void register_component(entt::meta_ctx &ctx);

        /**
         * Updates the animation.
         * If the animation is playing, it will update the current frame if the frame timer has reached 0.
         * If the animation is looping, it will reset the frame timer.
         * If the animation is not looping, it will stop the animation.
         * @param delta_time delta time
         */
        void update(std::chrono::duration<float> delta_time) noexcept;

        /**
         * Sets the frame timer interval.
         * @param interval interval
         */
        void set_timer(Timer timer);

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
    };
} // namespace missilengine
