#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missileengine
{
    class Game;
}

namespace missiletoad
{
    class MainMenuSystem : public missileengine::BaseSystem
    {
    public:
        MainMenuSystem(missileengine::Game *game);
        MainMenuSystem(const MainMenuSystem &) = delete;
        MainMenuSystem(MainMenuSystem &&)      = default;

        MainMenuSystem &operator=(const MainMenuSystem &) = delete;
        MainMenuSystem &operator=(MainMenuSystem &&)      = default;

        ~MainMenuSystem() override = default;

        void on_update(float delta_time) override;

        static void register_system(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
