#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class HealthComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        float max_health{100.0F};
        float health{100.0F};
    };
} // namespace missiletoad
