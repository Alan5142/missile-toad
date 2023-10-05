#pragma once
#include "missile_toad/core/common.hpp"
#include "missile_toad/core/texture.hpp"

#include <entt/meta/meta.hpp>
#include <entt/resource/resource.hpp>
#include <glm/vec4.hpp>

namespace missiletoad::core
{
    /**
     * @brief Sprite component.
     * @note This component is used to render a sprite.
     */
    class SpriteComponent
    {
    public:
        /**
         * @brief The texture of the sprite.
         */
        entt::resource<Texture> texture;

        std::optional<glm::vec4> scissors = std::nullopt;

        /**
         * @brief The z index of the sprite.
         */
        uint32_t z_index = 0;

        glm::u8vec4 color = glm::vec4(255.0f);

        /**
         * Registers the component with the meta context.
         * @param ctx
         */
        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad::core
