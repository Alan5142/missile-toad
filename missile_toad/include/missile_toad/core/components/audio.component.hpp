#pragma once
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad::core
{
    class AudioComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::core
