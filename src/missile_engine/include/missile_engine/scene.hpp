#pragma once
#include "base_system.hpp"
#include "common.hpp"
#include "entity_builder.hpp"

#include <LDtkLoader/Project.hpp>
#include <box2d/b2_world.h>
#include <entt/entity/registry.hpp>
#include <list>

namespace missileengine
{
    class Game;

    struct LayerInfo
    {
        std::string name;
        int         z_index;
        bool        has_collision = false;
    };

    /**
     * @brief The scene class contains all the entities and systems in the game.
     * In other words, a scene represents a level in the game.
     */
    class Scene
    {
    private:
        /**
         * @brief The entity registry for the scene.
         */
        entt::registry scene_entities_;
        /**
         * @brief A vector of pairs of system priorities and systems.
         */
        std::list<std::unique_ptr<BaseSystem>> systems_;

        b2World physics_world_{b2Vec2{0.0f, 0.0f}};

        Game *game_;

    public:
        Scene(Game *game);

        ~Scene() = default;

        Scene(const Scene &)            = delete;
        Scene(Scene &&)                 = delete;
        Scene &operator=(const Scene &) = delete;
        Scene &operator=(Scene &&)      = delete;

        /**
         * @brief Adds a system to the scene.
         * @note Order of addition matters as it determines the order of execution.
         * @tparam T The type of the system.
         * @tparam Args The types of the arguments to pass to the system's constructor.
         * @param args The arguments to pass to the system's constructor.
         * @return A pointer to the system.
         */
        template <typename T, typename... Args>
        void add_system(Args &&...args)
        {
            systems_.push_back(std::make_unique<T>(game_, std::forward<Args>(args)...));
        }

        /**
         * @brief Adds a system to the scene.
         * @see add_system<T, Args...>()
         * @param system
         */
        void add_system(std::unique_ptr<BaseSystem> system)
        {
            systems_.push_back(std::move(system));
        }

        void on_post_init();

        /**
         * @brief Calls the on_start() method of all the systems in the scene.
         */
        void on_start();

        /**
         * @brief Calls the on_destroy() method of all the systems in the scene.
         */
        void on_destroy();

        /**
         * @brief Updates all the systems in the scene.
         * @param delta_time The time in seconds since the last frame.
         */
        void update(float delta_time);

        /**
         * @brief Updates all the systems in the scene.
         * @param delta_time The time in seconds since the last frame.
         */
        void fixed_update(float delta_time);

        /**
         * @brief Renders all the systems in the scene.
         */
        void on_render();

        /**
         * @brief Gets the entity registry of the scene.
         * @return A reference to the entity registry of the scene.
         */
        entt::registry &get_registry() noexcept
        {
            return scene_entities_;
        }

        /**
         * @brief Gets the entity registry of the scene.
         * @return A const reference to the entity registry of the scene.
         */
        [[nodiscard]] const entt::registry &get_registry() const noexcept
        {
            return scene_entities_;
        }

        /**
         * @brief Gets the systems of the scene.
         * @return A reference to the systems of the scene.
         */
        [[nodiscard]] const std::list<std::unique_ptr<BaseSystem>> &get_systems() const noexcept
        {
            return systems_;
        }

        /**
         * @brief Gets the list of entities with the specified components.
         * @tparam Args The types of the components.
         * @return A view of the entities with the specified components.
         */
        template <typename... C, typename... Args>
        [[nodiscard]] decltype(auto) view(Args &&...args) const noexcept
        {
            return scene_entities_.view<C...>(std::forward<Args>(args)...);
        }

        template <typename... C, typename... Args>
        [[nodiscard]] decltype(auto) view(Args &&...args) noexcept
        {
            return scene_entities_.view<C...>(std::forward<Args>(args)...);
        }

        template <typename T>
        [[nodiscard]] decltype(auto) get_component(entt::entity entity) const noexcept
        {
            return scene_entities_.get<T>(entity);
        }

        template <typename T>
        [[nodiscard]] decltype(auto) get_component(entt::entity entity) noexcept
        {
            return scene_entities_.get<T>(entity);
        }

        template <typename T>
        [[nodiscard]] decltype(auto) try_get_component(entt::entity entity) const noexcept
        {
            return scene_entities_.try_get<T>(entity);
        }

        template <typename T>
        [[nodiscard]] decltype(auto) try_get_component(entt::entity entity) noexcept
        {
            return scene_entities_.try_get<T>(entity);
        }

        void segment_loader(const ldtk::World &ldtk_world, std::string_view level_name,
                            const std::vector<LayerInfo>             &layers,
                            std::function<void(const ldtk::Entity &)> on_entity_create = {});

        entt::entity get_entity_with_tag(std::string_view tag);

        /**
         * @brief Creates an entity builder.
         * @return An entity builder.
         */
        EntityBuilder create_entity();

    private:
        friend class PhysicsSystem;
        friend struct Physics;
    };
} // namespace missileengine
