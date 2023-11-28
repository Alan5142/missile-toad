#pragma once
#include "missile_engine/common.hpp"

#include <entt/entity/entity.hpp>
#include <glm/vec2.hpp>
#include <optional>

namespace missileengine
{
    /**
     * The result of a raycast.
     */
    struct RaycastResult
    {
        /**
         * The point where the raycast hit.
         */
        glm::vec2 point;
        /**
         * The normal of the surface where the raycast hit.
         */
        glm::vec2 normal;
        /**
         * The fraction of the raycast.
         */
        float fraction;
        /**
         * The entity that was hit.
         */
        entt::entity entity;
    };

    struct Physics
    {
        /**
         * @brief Raycasts from start to end.
         * @param start point in world space to start the raycast.
         * @param end point in world space to end the raycast.
         * @return The result of the raycast. If the raycast didn't hit anything, it returns std::nullopt.
         */
        [[nodiscard]] static std::optional<RaycastResult> raycast(glm::vec2 start, glm::vec2 end);

        /**
         * @brief Raycasts from start in the given direction up until the given distance, starting from start.
         * @param start point in world space to start the raycast.
         * @param direction a vector representing the direction of the raycast.
         * @param distance the distance of the raycast.
         * @return The result of the raycast. If the raycast didn't hit anything, it returns std::nullopt.
         */
        [[nodiscard]] static std::optional<RaycastResult> raycast(glm::vec2 start, glm::vec2 direction, float distance);

        /**
         * @brief constant for the up direction.
         */
        static constexpr glm::vec2 UP = {0.0F, -1.0F};

        /**
         * @brief constant for the down direction.
         */
        static constexpr glm::vec2 DOWN = {0.0F, 1.0F};

        /**
         * @brief constant for the left direction.
         */
        static constexpr glm::vec2 LEFT = {-1.0F, 0.0F};

        /**
         * @brief constant for the right direction.
         */
        static constexpr glm::vec2 RIGHT = {1.0F, 0.0F};
    };
} // namespace missileengine
