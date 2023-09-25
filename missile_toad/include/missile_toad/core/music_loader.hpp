#pragma once

#include "common.hpp"
#include "music.hpp"

namespace missiletoad::core
{
    /**
     * @brief Loads a music from the VFS.
     */
    class MusicLoader final
    {
    public:
        /**
         * @brief The result type of the loader.
         */
        using result_type = std::shared_ptr<Music>;

        /**
         * Loads a music from the VFS.
         * @param name The name of the music to load.
         * @return The loaded music.
         */
        result_type operator()(std::string_view name) const;
    };
} // namespace missiletoad::core
