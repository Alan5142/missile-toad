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

        void on_update(float delta_time) override;
    };
} // namespace missileengine
