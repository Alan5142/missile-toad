#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class KingMechaRatComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
