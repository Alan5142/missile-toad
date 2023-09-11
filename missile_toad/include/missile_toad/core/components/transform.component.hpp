#pragma once
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>
#include <glm/vec2.hpp>

namespace missiletoad::core
{
    class TransformComponent
    {
    public:
        glm::vec2 position;
        glm::vec2 scale;
        float     rotation;

        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::core
