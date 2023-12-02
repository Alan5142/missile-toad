#pragma once
#include "missile_engine/common.hpp"
#include "missile_engine/movie.hpp"
#include "missile_engine/texture.hpp"

#include <entt/meta/meta.hpp>
#include <entt/resource/resource.hpp>
#include <glm/vec2.hpp>

namespace missileengine
{
    /**
     * @brief A component that can play a mpeg movie.
     */
    class MoviePlayerComponent
    {
    public:
        entt::resource<Movie> movie;

        static void register_component(entt::meta_ctx &ctx);

        /**
         * @brief Construct a new Movie Player Component object
         * @param movie A reference to the movie resource to play.
         */
        explicit MoviePlayerComponent(entt::resource<Movie> movie) : movie(std::move(movie))
        {
        }
    };
} // namespace missileengine
