#pragma once
#include "missile_engine/common.hpp"
#include "missile_engine/music.hpp"

#include <entt/meta/meta.hpp>
#include <entt/resource/resource.hpp>

namespace missilengine
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
} // namespace missilengine
