#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>
#include <glm/vec2.hpp>

namespace missiletoad
{
    class BulletComponent
    {
    public:
        float     velocity  = 1.0f;
        glm::vec2 direction = {};

        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad