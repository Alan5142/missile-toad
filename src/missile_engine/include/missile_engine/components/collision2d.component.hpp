#pragma once
#include "missile_engine/common.hpp"

#include <entt/entity/entity.hpp>
#include <entt/meta/meta.hpp>

namespace missilengine
{
    /**
     * @brief 2D collision status.
     */
    enum class ECollisionStatus
    {
        /**
         * Collision started.
         */
        ENTER,
        /**
         * Collision ended.
         */
        EXIT
    };

    /**
     * @brief Component that handles 2D collisions. It provides a callback that is called when a collision occurs.
     * @note the callback is called for both entities involved in the collision. The callback is called inside
     * fixed_update().
     */
    class Collision2dComponent
    {
    public:
        /**
         * @brief Callback that is called when a collision occurs.
         */
        std::function<void(entt::entity self, entt::entity other, ECollisionStatus status)> callback;
        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missilengine
