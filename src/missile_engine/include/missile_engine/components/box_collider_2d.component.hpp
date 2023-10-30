#pragma once
#include "missile_engine/common.hpp"

#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <entt/meta/meta.hpp>
#include <glm/vec2.hpp>

namespace missileengine
{
    /**
     * A box collider component.
     * @note This component is used for 2d physics.
     */
    class BoxCollider2dComponent
    {
        /**
         * The fixture of the collider.
         */
        b2Fixture *fixture_{};
        friend class PhysicsSystem;

    public:
        /**
         * Registers the component with entt.
         * @param ctx
         */
        static void register_component(entt::meta_ctx &ctx);

        /**
         * Constructs a box collider component.
         */
        BoxCollider2dComponent();

        // Size and position are handled in the transform component.

        /**
         * Sets whether or not the collider is a sensor.
         * @note A sensor is a collider that does not collide with other colliders. (known as a trigger in Unity)
         * @param is_sensor whether or not the collider is a sensor.
         */
        void set_sensor(bool is_sensor);

        /**
         * Sets the friction of the collider.
         * @note Friction is the amount of friction the collider has.
         * @note A friction of 0 means no friction, and a friction of 1 means full friction.
         * @param friction friction
         */
        void set_friction(float friction);

        /**
         * Sets the restitution of the collider.
         * @note Restitution is the bounciness of the collider.
         * @param restitution restitution
         */
        void set_restitution(float restitution);

        /**
         * Sets the density of the collider.
         * @note Density is the mass of the collider (
         * @param density density
         */
        void set_density(float density);

        /**
         * Sets the size of the collider.
         * @param size size
         */
        void set_size(glm::vec2 size);

        /**
         * Gets the fixture of the collider.
         * @return
         */
        [[nodiscard]] b2Fixture *get_fixture() const;

        /**
         * Gets whether or not the collider is a sensor.
         * @return whether or not the collider is a sensor.
         */
        [[nodiscard]] bool is_sensor() const;

        /**
         * Gets the friction of the collider.
         * @return friction
         */
        [[nodiscard]] float get_friction() const;

        /**
         * Gets the restitution of the collider.
         * @return restitution
         */
        [[nodiscard]] float get_restitution() const;

        /**
         * Gets the density of the collider.
         * @return density
         */
        [[nodiscard]] float get_density() const;
    };
} // namespace missileengine
