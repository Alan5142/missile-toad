#pragma once
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad::game
{
    class PlayerComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        float hola;
    };
} // namespace missiletoad::game
