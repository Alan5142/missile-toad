#pragma once

#include "common.hpp"
#include "movie.hpp"

namespace missileengine
{
    /**
     * @brief Loads a music from the VFS.
     */
    class MovieLoader final
    {
    public:
        /**
         * @brief The result type of the loader.
         */
        using result_type = std::shared_ptr<Movie>;

        /**
         * Loads a music from the VFS.
         * @param name The name of the music to load.
         * @return The loaded music.
         */
        result_type operator()(std::string_view name) const;
    };
} // namespace missileengine
