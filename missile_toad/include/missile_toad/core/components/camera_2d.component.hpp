#pragma once
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>
#include <raylib-cpp.hpp>

namespace missiletoad::core
{
    class Camera2dComponent
    {
    public:
        raylib::Camera2D camera;
        static void      register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::core
