#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>

namespace missileengine
{
    class Game;

    class AudioSystem : public missileengine::BaseSystem
    {
        entt::registry *registry_;

    public:
        AudioSystem(Game *game);
        AudioSystem(const AudioSystem &) = delete;
        AudioSystem(AudioSystem &&)      = delete;

        AudioSystem &operator=(const AudioSystem &) = delete;
        AudioSystem &operator=(AudioSystem &&)      = delete;

        ~AudioSystem() override;

        static void register_system(entt::meta_ctx &ctx);

        void on_update(float delta_time) override;
    }; // namespace missileengine
} // namespace missileengine
