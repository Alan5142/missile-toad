#pragma once
#include "missile_engine/common.hpp"

#include <box2d/b2_body.h>
#include <entt/meta/meta.hpp>
#include <glm/vec2.hpp>

class ContactListener;

namespace missilengine
{
    class PhysicsSystem;

    class Rigidbody2dComponent
    {
        b2Body *body_{};

        friend class PhysicsSystem;

    public:
        static void register_component(entt::meta_ctx &ctx);

        Rigidbody2dComponent() = default;

        /**
         * Sets whether or not the body is static.
         * @note a static body is immovable.
         * @param is_static whether or not the body is static.
         */
        void set_static(bool is_static);

        /**
         * Sets the linear velocity of the body.
         * @param x
         * @param y
         */
        void set_linear_velocity(glm::vec2 force);

        /**
         * Applies a force to the body.
         * @param force force to apply
         * @param point point of application
         */
        void apply_force(glm::vec2 force, glm::vec2 point);

        /**
         * Applies a force to the center of the body.
         * @param force force
         */
        void apply_force_to_center(glm::vec2 force);

        /**
         * Applies a torque to the body.
         * @param torque
         */
        void apply_torque(float torque);

        /**
         * Applies a linear impulse to the body.
         * @param force force to apply
         * @param point point of application
         */
        void apply_linear_impulse(glm::vec2 force, glm::vec2 point);

        /**
         * Applies a linear impulse to the center of the body.
         * @param force force to apply to the center of the body.
         */
        void apply_linear_impulse_to_center(glm::vec2 force);

        /**
         * Sets whether or not the body is a bullet.
         * @note a bullet body is a body that is not affected by tunneling.
         * @param is_bullet whether or not the body is a bullet.
         */
        void set_is_bullet(bool is_bullet);

        /**
         * Sets whether or not the body is fixed rotation.
         * @note a fixed rotation body is a body that cannot rotate.
         * @param is_fixed_rotation whether or not the body is fixed rotation.
         */
        void set_is_fixed_rotation(bool is_fixed_rotation);

        /**
         * Gets the body.
         * @return the body.
         */
        [[nodiscard]] b2Body *get_body() const;

        /**
         * Gets whether or not the body is static.
         * @note a static body is immovable.
         * @return whether or not the body is static.
         */
        [[nodiscard]] bool is_static() const;

        /**
         * Gets whether or not the body is dynamic.
         * @note a dynamic body is movable.
         * @return whether or not the body is dynamic.
         */
        [[nodiscard]] bool is_dynamic() const;

        /**
         * Gets the linear velocity of the body.
         * @return linear velocity of the body.
         */
        [[nodiscard]] glm::vec2 get_linear_velocity() const;

        /**
         * Gets the angular velocity of the body.
         * @return angular velocity of the body.
         */
        [[nodiscard]] float get_angular_velocity() const;

        /**
         * Gets whether or not the body is a bullet.
         * @note a bullet body is a body that is not affected by tunneling.
         * @return whether or not the body is a bullet.
         */
        [[nodiscard]] bool is_bullet() const;

        /**
         * Gets whether or not the body is fixed rotation.
         * @return whether or not the body is fixed rotation.
         */
        [[nodiscard]] bool is_fixed_rotation() const;
    };
} // namespace missilengine
