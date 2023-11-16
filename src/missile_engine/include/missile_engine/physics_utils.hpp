#pragma once
#include "missile_engine/common.hpp"

#include <entt/entity/entity.hpp>
#include <glm/vec2.hpp>
#include <optional>

namespace missileengine
{

    struct RaycastResult
    {
        glm::vec2    point;
        glm::vec2    normal;
        float        fraction;
        entt::entity entity;
    };

    struct Physics
    {
        [[nodiscard]] static std::optional<RaycastResult> raycast(glm::vec2 start, glm::vec2 end);

        [[nodiscard]] static std::optional<RaycastResult> raycast(glm::vec2 start, glm::vec2 direction, float distance);

        static constexpr glm::vec2 UP    = {0.0F, -1.0F};
        static constexpr glm::vec2 DOWN  = {0.0F, 1.0F};
        static constexpr glm::vec2 LEFT  = {-1.0F, 0.0F};
        static constexpr glm::vec2 RIGHT = {1.0F, 0.0F};
    };
} // namespace missileengine
