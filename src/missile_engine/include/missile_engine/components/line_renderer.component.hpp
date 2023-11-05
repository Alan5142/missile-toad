#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace missileengine
{
    /**
     * @brief A component that renders a line between two points.
     */
    class LineRendererComponent
    {
        static constexpr glm::u8vec4 DEFAULT_COLOR = {255, 255, 255, 255};

    public:
        static void register_component(entt::meta_ctx &ctx);

        /**
         * @brief The start point of the line.
         */
        glm::vec2 start{};

        /**
         * @brief The end point of the line.
         */
        glm::vec2 end{};

        /**
         * @brief The color of the line.
         */
        glm::u8vec4 color = DEFAULT_COLOR;

        /**
         * @brief The width of the line.
         */
        float width{1.0F};
    };
} // namespace missileengine
