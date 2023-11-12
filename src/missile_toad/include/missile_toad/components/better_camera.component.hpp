#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class BetterCameraComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        float   x_offset     = 0.0F;
        float   y_offset     = 0.0F;
        float   follow_speed = 0.0F;
        uint8_t is_x_locked  = 0;
        uint8_t is_y_locked  = 0;
    };
} // namespace missiletoad
