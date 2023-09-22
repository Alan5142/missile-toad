#pragma once
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/common.hpp"

#include <box2d/b2_world.h>
#include <entt/entity/observer.hpp>
#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>

namespace missiletoad::core
{
    class Locator;

    class PhysicsSystem : public missiletoad::core::BaseSystem
    {
        b2World         world_;
        entt::observer  transform_observer_;
        entt::registry *registry_;
        Locator        *locator_;

    public:
        PhysicsSystem(Locator &locator);
        PhysicsSystem(const PhysicsSystem &)        = delete;
        PhysicsSystem(PhysicsSystem &&rhs) noexcept = delete;

        PhysicsSystem &operator=(const PhysicsSystem &)        = delete;
        PhysicsSystem &operator=(PhysicsSystem &&rhs) noexcept = delete;

        ~PhysicsSystem() override;

        static void register_system(entt::meta_ctx &ctx);

        void on_fixed_update(float delta_time) override;

    private:
        /**
         * Called when a box collider is created.
         * @param registry registry
         * @param entity entity
         */
        void on_box_collider_created(entt::registry &registry, entt::entity entity);

        /**
         * Called when a rigidbody is created.
         * @param registry registry
         * @param entity entity
         */
        void on_rigidbody_created(entt::registry &registry, entt::entity entity);
    };
} // namespace missiletoad::core
