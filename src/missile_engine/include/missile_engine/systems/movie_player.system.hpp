#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missileengine
{
    class Game;
}

namespace missileengine
{
    /**
     * @brief A system that plays movies.
     * This decompresses the movie frames and renders them to a texture.
     */
    class MoviePlayerSystem final : public missileengine::BaseSystem
    {
    public:
        explicit MoviePlayerSystem(Game *game);

        MoviePlayerSystem(const MoviePlayerSystem &)            = delete;
        MoviePlayerSystem(MoviePlayerSystem &&)                 = default;
        MoviePlayerSystem &operator=(const MoviePlayerSystem &) = delete;
        MoviePlayerSystem &operator=(MoviePlayerSystem &&)      = default;

        ~MoviePlayerSystem() override = default;

        static void register_system(entt::meta_ctx &ctx);

        /**
         * @brief Updates the system, allowing it to play movies.
         */
        void on_update(float delta_time) override;
    };
} // namespace missileengine
