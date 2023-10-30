#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missileengine
{
    /**
     * @brief Tag component. It includes a string that can be used to give a tag to an entity.
     */
    class TagComponent
    {
    public:
        /**
         * @brief Entity tag.
         */
        std::string tag;

        /**
         * @brief Register the component to the meta context.
         * @param ctx Meta context.
         */
        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missileengine
