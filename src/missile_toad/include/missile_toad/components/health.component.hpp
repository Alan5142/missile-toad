#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class HealthComponent
    {
        float max_health{100.0F};
        float health{100.0F};

    public:
        static void register_component(entt::meta_ctx &ctx);

        void take_damage(float damage)
        {
            if (health - damage < 0.0F)
            {
                health = 0.0F;
                return;
            }
            health -= damage;
        }
        bool is_dead() const
        {
            return health <= 0.0F;
        }

        float get_health() const
        {
            return health;
        }

        float get_max_health() const
        {
            return max_health;
        }

        float get_health_percentage() const
        {
            return health / max_health;
        }
    };
} // namespace missiletoad
