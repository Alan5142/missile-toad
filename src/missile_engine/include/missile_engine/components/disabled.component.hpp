#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missileengine
{
    /**
     * @brief Component that disables an entity.
     *
     */
    class DisabledComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        bool dummy = false;
    };
} // namespace missileengine
