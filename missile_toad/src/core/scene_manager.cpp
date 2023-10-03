#include "missile_toad/core/scene_manager.hpp"
#include "missile_toad/core/game.hpp"
#include "missile_toad/core/scene.hpp"
#include "missile_toad/core/scene_descriptor.hpp"

missiletoad::core::SceneManager::SceneManager(missiletoad::core::Game &game) noexcept : game_(game)
{
}

missiletoad::core::Scene *missiletoad::core::SceneManager::active_scene()
{
    return active_scene_.get();
}

void missiletoad::core::SceneManager::load_scene(std::string_view name)
{
    next_scene_ = name;
}

class MetaSystem : public missiletoad::core::BaseSystem
{
    entt::meta_any underlying_;

public:
    MetaSystem(entt::meta_any &&underlying) : underlying_(std::move(underlying))
    {
        (void)1;
    }

    void on_update(float delta_time) override
    {
        underlying_.cast<missiletoad::core::BaseSystem &>().on_update(delta_time);
    }

    void on_render() override
    {
        underlying_.cast<missiletoad::core::BaseSystem &>().on_render();
    }

    void on_fixed_update(float delta_time) override
    {
        underlying_.cast<missiletoad::core::BaseSystem &>().on_fixed_update(delta_time);
    }

    void on_destroy() override
    {
        underlying_.cast<missiletoad::core::BaseSystem &>().on_destroy();
    }

    void on_start() override
    {
        underlying_.cast<missiletoad::core::BaseSystem &>().on_start();
    }
};

void missiletoad::core::SceneManager::on_post_update()
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

            auto *base_system = instance.try_cast<missiletoad::core::BaseSystem>();
            if (base_system == nullptr)
            {
                spdlog::warn("Failed to cast system type to BaseSystem: {}", system);
                continue;
            }
            active_scene_->add_system<MetaSystem>(std::move(instance));
        }
        active_scene_->on_post_init();
        active_scene_->on_start();
    }
}
