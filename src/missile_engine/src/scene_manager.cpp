#include "missile_engine/scene_manager.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/scene.hpp"
#include "missile_engine/scene_descriptor.hpp"

missileengine::SceneManager::SceneManager(missileengine::Game &game) noexcept : game_(game)
{
}

missileengine::Scene *missileengine::SceneManager::active_scene()
{
    return active_scene_.get();
}

void missileengine::SceneManager::load_scene(std::string_view name)
{
    next_scene_ = name;
}

class MetaSystem : public missileengine::BaseSystem
{
    entt::meta_any underlying_;

public:
    MetaSystem(missileengine::Game *game, entt::meta_any &&underlying) : underlying_(std::move(underlying))
    {
        unused(game);
    }

    void on_update(float delta_time) override
    {
        underlying_.cast<missileengine::BaseSystem &>().on_update(delta_time);
    }

    void on_render() override
    {
        underlying_.cast<missileengine::BaseSystem &>().on_render();
    }

    void on_fixed_update(float delta_time) override
    {
        underlying_.cast<missileengine::BaseSystem &>().on_fixed_update(delta_time);
    }

    void on_destroy() override
    {
        underlying_.cast<missileengine::BaseSystem &>().on_destroy();
    }

    void on_start() override
    {
        underlying_.cast<missileengine::BaseSystem &>().on_start();
    }
};

void missileengine::SceneManager::on_post_update()
{
    if (next_scene_.has_value())
    {
        auto descriptor_opt = load_scene_descriptor(next_scene_.value());
        if (!descriptor_opt.has_value())
        {
            spdlog::error("Failed to load scene descriptor for scene: {}", next_scene_.value());
            return;
        }
        next_scene_ = std::nullopt;

        auto &descriptor = descriptor_opt.value();
        if (active_scene_ != nullptr)
        {
            active_scene_->on_destroy();
            active_scene_.reset();
        }
        active_scene_ = std::make_unique<Scene>(&game_);

        active_scene_->on_post_init();

        auto &systems_db = game_.systems_meta_ctx();
        for (auto &system : descriptor.systems)
        {
            auto system_type = entt::resolve(systems_db, entt::hashed_string::value(system.c_str(), system.length()));

            if (!system_type)
            {
                spdlog::error("Failed to resolve system type: {}", system);
                continue;
            }

            auto instance = system_type.construct(&game_);
            if (!instance)
            {
                spdlog::error("Failed to construct system type: {}", system);
                continue;
            }

            auto *base_system = instance.try_cast<missileengine::BaseSystem>();
            if (base_system == nullptr)
            {
                spdlog::warn("Failed to cast system type to BaseSystem: {}", system);
                continue;
            }
            active_scene_->add_system<MetaSystem>(std::move(instance));
        }
        active_scene_->on_start();
    }
}
