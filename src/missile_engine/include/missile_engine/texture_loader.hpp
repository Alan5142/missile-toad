#pragma once

#include "common.hpp"
#include "texture.hpp"

namespace missileengine
{
    /**
     * @brief Loads a texture from the VFS.
     */
    class TextureLoader final
    {
    public:
        /**
         * @brief The result type of the loader.
         */
        using result_type = std::shared_ptr<Texture>;

        /**
         * Loads a texture from the VFS.
         * @param name The name of the texture to load.
         * @return The loaded texture.
         */
        result_type operator()(std::string_view name) const;
    };
} // namespace missileengine
