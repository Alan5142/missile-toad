#pragma once
#include "missile_toad/core/common.hpp"
#include "missile_toad/core/texture.hpp"

#include <entt/meta/meta.hpp>
#include <entt/resource/resource.hpp>

namespace missiletoad::core
{
    class SpriteComponent
    {
    public:
        entt::resource<Texture> texture;
        uint32_t                z_index;
        static void             register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::core
