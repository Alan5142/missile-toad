#pragma once
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/common.hpp"

#include <box2d/b2_world.h>
#include <entt/entity/observer.hpp>
#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>

namespace missiletoad::core
{
    class PhysicsSystem : public missiletoad::core::BaseSystem
    {
        b2World        world_;
        entt::observer transform_observer_;

    public:
        PhysicsSystem();

        static void register_system(entt::meta_ctx &ctx);

        void on_fixed_update(float delta_time) override;
    };
} // namespace missiletoad::core
