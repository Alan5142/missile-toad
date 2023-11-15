#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class TurretComponent
    {
    public:
        int TURRET_MAX_SHOTS = 200;

        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
