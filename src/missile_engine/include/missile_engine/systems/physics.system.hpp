#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <box2d/b2_world.h>
#include <entt/entity/observer.hpp>
#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>

namespace missileengine
{
    class Game;

    /**
     * @brief The physics system.
     * This system handles all physics in the game.
     */
    class PhysicsSystem : public missileengine::BaseSystem
    {
        /**
         * @brief Save in a list rigid bodies to be destroyed
         */
        std::vector<b2Body *> rigidbodies_to_destroy_;

        /**
         * @brief The physics world.
         */
        b2World *world_;
        /**
         * @brief The observer for the transform component.
         */
        entt::observer transform_observer_;

        /**
         * @brief The registry.
         */
        entt::registry *registry_;

    public:
        PhysicsSystem(Game *game);
        PhysicsSystem(const PhysicsSystem &)        = delete;
        PhysicsSystem(PhysicsSystem &&rhs) noexcept = delete;

        PhysicsSystem &operator=(const PhysicsSystem &)        = delete;
        PhysicsSystem &operator=(PhysicsSystem &&rhs) noexcept = delete;

        ~PhysicsSystem() override;

        static void register_system(entt::meta_ctx &ctx);

        /**
         * @brief Updates the physics system. It uses a fixed timestep, that's why
         * it uses fixed_update instead of update.
         * @param delta_time The delta time.
         */
        void on_fixed_update(float delta_time) override;

    private:
        /**
         * Called when a box collider is created.
         * @param registry registry
         * @param entity entity
         */
        void on_box_collider_created(entt::registry &registry, entt::entity entity);

        /**
         * @brief Called when a circle collider is created.
         * @param registry registry
         * @param entity entity
         */
        void on_circle_collider_created(entt::registry &registry, entt::entity entity);

        /**
         * Called when a rigidbody is created.
         * @param registry registry
         * @param entity entity
         */
        void on_rigidbody_created(entt::registry &registry, entt::entity entity);

        /**
         * Called when an entity is disabled.
         * @param registry registry
         * @param entity entity
         */
        void on_entity_disabled(entt::registry &registry, entt::entity entity);

        /**
         * Called when an entity is enabled.
         * @param registry registry
         * @param entity entity
         */
        void on_entity_enabled(entt::registry &registry, entt::entity entity);

        void on_rigidbody_destroyed(entt::registry &registry, entt::entity entity);
    };
} // namespace missileengine
