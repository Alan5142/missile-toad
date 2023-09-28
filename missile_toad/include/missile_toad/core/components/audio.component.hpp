#pragma once
#include "missile_toad/core/common.hpp"
#include "missile_toad/core/music.hpp"

#include <entt/meta/meta.hpp>
#include <entt/resource/resource.hpp>

namespace missiletoad::core
{
    class AudioComponent
    {
    public:
        /**
         * @brief An audio to be played.
         */
        entt::resource<Music> sound;
        static void           register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::core
