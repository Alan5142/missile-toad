#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class TurretComponent
    {
    public:
        static void register_component(entt::meta_ctx& ctx);

                float turret_speed = 4.4F;
    };
}
