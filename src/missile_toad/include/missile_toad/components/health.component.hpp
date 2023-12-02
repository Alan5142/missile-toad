#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class HealthComponent
    {
        float max_health_{100.0F};
        float health_{100.0F};

    public:
        static void register_component(entt::meta_ctx &ctx);

        void take_damage(float damage)
        {
            spdlog::info("Enemy has {} hp and takes {} dp", health_, damage);
            if (health_ - damage < 0.0F)
            {
                health_ = 0.0F;
                spdlog::info("Enemy has {} health points.", health_);
                return;
            }
            health_ -= damage;
            spdlog::info("Enemy has {} health points left.", health_);
        }
        [[nodiscard]] bool is_dead() const
        {
            return health_ <= 0.0F;
        }

        [[nodiscard]] float get_health() const
        {
            return health_;
        }

        [[nodiscard]] float get_max_health() const
        {
            return max_health_;
        }

        [[nodiscard]] float get_health_percentage() const
        {
            return health_ / max_health_;
        }
    };
} // namespace missiletoad
