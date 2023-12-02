#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>

namespace missileengine
{
    class Game;

    /**
     * @brief The audio system.
     */
    class AudioSystem : public missileengine::BaseSystem
    {
        /**
         * @brief a pointer to the registry.
         */
        entt::registry *registry_;

    public:
        AudioSystem(Game *game);
        AudioSystem(const AudioSystem &) = delete;
        AudioSystem(AudioSystem &&)      = delete;

        AudioSystem &operator=(const AudioSystem &) = delete;
        AudioSystem &operator=(AudioSystem &&)      = delete;

        ~AudioSystem() override;

        static void register_system(entt::meta_ctx &ctx);

        /**
         * @brief Updates the system, allowing it to play sounds.
         */
        void on_update(float delta_time) override;
    }; // namespace missileengine
} // namespace missileengine
