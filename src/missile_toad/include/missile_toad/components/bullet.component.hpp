#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class BulletComponent
    {
    public:
        int MAX_SHOTS = 200;

        
        static void register_component(entt::meta_ctx& ctx);
    };
}
