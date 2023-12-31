#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class PlayerComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        float player_speed = 4.4F;
    };
} // namespace missiletoad
