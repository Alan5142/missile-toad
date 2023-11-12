#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>
#include <glm/vec2.hpp>
#include <raylib-cpp.hpp>

namespace missileengine
{
    /**
     * @brief 2D camera component.
     */
    class Camera2dComponent
    {
        /**
         * @brief Raylib camera.
         */
        raylib::Camera2D camera_{raylib::Vector2{0.0F, 0.0F}, raylib::Vector2{0.0F, 0.0F}, 0.0F, 1.0F};

        std::unique_ptr<raylib::RenderTexture2D> render_texture_;

        bool main_camera_ = false;

    public:
        /**
         * @brief Construct a new Camera 2d Component object
         * @param texture_size The size of the texture to render to.
         * @param main_camera  Whether or not this is the main camera.
         */
        Camera2dComponent(glm::u32vec2 texture_size, bool main_camera = false);

        Camera2dComponent(const Camera2dComponent &)            = delete;
        Camera2dComponent(Camera2dComponent &&)                 = default;
        Camera2dComponent &operator=(const Camera2dComponent &) = delete;
        Camera2dComponent &operator=(Camera2dComponent &&)      = default;
        ~Camera2dComponent()                                    = default;

        /**
         * Registers the component with the meta context.
         * @param ctx meta context
         */
        static void register_component(entt::meta_ctx &ctx);

        /**
         * Sets the zoom of the camera.
         * @param zoom zoom
         */
        void set_zoom(float zoom)
        {
            camera_.zoom = zoom;
        }

        /**
         * Sets the target of the camera.
         * @param target target
         */
        void set_target(glm::vec2 target)
        {
            camera_.target = {target.x, target.y};
        }

        /**
         * Sets the rotation of the camera.
         * @param rotation rotation
         */
        void set_rotation(float rotation)
        {
            camera_.rotation = rotation;
        }

        /**
         * Sets the offset of the camera.
         * @param offset offset
         */
        void set_offset(glm::vec2 offset)
        {
            camera_.offset = {offset.x, offset.y};
        }

        /**
         * Gets the zoom of the camera.
         * @return zoom
         */
        [[nodiscard]] float get_zoom() const
        {
            return camera_.zoom;
        }

        /**
         * Gets the target of the camera.
         * @return target
         */
        [[nodiscard]] glm::vec2 get_target() const
        {
            return {camera_.target.x, camera_.target.y};
        }

        /**
         * Gets the offset of the camera.
         * @return offset
         */
        [[nodiscard]] glm::vec2 get_offset() const
        {
            return {camera_.offset.x, camera_.offset.y};
        }

        /**
         * Gets the screen position of the world position.
         * @param screen_pos screen position
         * @return world position
         */
        [[nodiscard]] glm::vec2 get_screen_to_world(glm::vec2 screen_pos) const
        {
            auto world_pos = ::GetScreenToWorld2D({screen_pos.x, screen_pos.y}, camera_);
            return {world_pos.x/missileengine::PIXELS_PER_UNIT, world_pos.y/missileengine::PIXELS_PER_UNIT};
        }

        /**
         * Gets the world position of the screen position.
         * @param world_pos world position
         * @return screen position
         */
        [[nodiscard]] glm::vec2 get_world_to_screen(glm::vec2 world_pos) const
        {
            auto screen_pos = ::GetWorldToScreen2D({world_pos.x, world_pos.y}, camera_);
            return {screen_pos.x, screen_pos.y};
        }

        /**
         * Gets the underlying raylib camera.
         * @return raylib camera
         */
        Camera2D &get_camera()
        {
            return camera_;
        }

        /**
         * Gets the underlying raylib camera.
         * @return raylib camera
         */
        [[nodiscard]] const Camera2D &get_camera() const
        {
            return camera_;
        }

        /**
         * Gets the underlying raylib render texture.
         * @return raylib render texture
         */
        [[nodiscard]] raylib::RenderTexture2D &get_render_texture()
        {
            return *render_texture_;
        }

        [[nodiscard]] bool is_main_camera() const
        {
            return main_camera_;
        }

        void set_is_main_camera(bool main_camera)
        {
            main_camera_ = main_camera;
        }
    };
} // namespace missileengine
