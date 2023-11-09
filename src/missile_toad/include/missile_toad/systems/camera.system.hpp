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
    class CameraSystem : public missileengine::BaseSystem
    {
    public:
        CameraSystem(missileengine::Game *game);

        CameraSystem(const CameraSystem &)            = delete;
        CameraSystem(CameraSystem &&)                 = default;
        CameraSystem &operator=(const CameraSystem &) = delete;
        CameraSystem &operator=(CameraSystem &&)      = default;

        ~CameraSystem() override = default;

        void on_update(float delta_time) override;

        static void register_system(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
