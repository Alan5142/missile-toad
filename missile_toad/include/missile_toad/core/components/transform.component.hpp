#pragma once
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>
#include <glm/vec2.hpp>

namespace missiletoad::core
{
    /**
     * @brief Class that represents a transform.
     * @details A transform is a position, scale, and rotation.
     */
    class TransformComponent
    {
    public:
        /**
         * @brief The position of the transform.
         */
        glm::vec2 position;

        /**
         * @brief The scale of the transform.
         */
        glm::vec2 scale;

        /**
         * @brief The rotation of the transform.
         */
        float rotation;

        /**
         * Registers the component with the meta context.
         * @param ctx meta context
         */
        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::core
