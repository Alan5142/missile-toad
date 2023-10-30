#pragma once
#include "common.hpp"
#include "components/tag.component.hpp"

#include <entt/entity/registry.hpp>

namespace missileengine
{
    /**
     * @brief Builder for entities
     */
    class EntityBuilder
    {
        /**
         * @brief The registry to create the entity in
         */
        entt::registry *registry_;

        /**
         * @brief The created entity
         */
        entt::entity entity_;

        /**
         * @brief Whether the entity has been built. Used to destroy the entity when the builder is
         * destroyed and the entity has not been built.
         */
        bool has_been_built_ = false;

    public:
        /**
         * Creates a new entity builder
         * @param registry registry to create the entity in.
         */
        EntityBuilder(entt::registry *registry) : registry_(registry), entity_(registry->create())
        {
            // Add tag component to entity
            registry_->emplace<missileengine::TagComponent>(entity_, "Entity ");
        }

        EntityBuilder(const EntityBuilder &)            = delete;
        EntityBuilder(EntityBuilder &&)                 = delete;
        EntityBuilder &operator=(const EntityBuilder &) = delete;
        EntityBuilder &operator=(EntityBuilder &&)      = delete;

        ~EntityBuilder()
        {
            if (!has_been_built_)
            {
                registry_->destroy(entity_);
            }
        }

        /**
         * @brief Adds a component to the entity
         * @tparam T type of component
         * @tparam Args types of arguments to pass to the component constructor
         * @param args arguments to pass to the component constructor
         * @return reference to this
         */
        template <typename T, typename... Args>
        [[nodiscard]] EntityBuilder &with_component(Args &&...args)
        {
            unused(registry_->get_or_emplace<T>(entity_, std::forward<Args>(args)...));
            return *this;
        }

        /**
         * @brief Adds a component to the entity from a function
         * @tparam T type of component
         * @tparam Func type of function
         * @param func function to call to get the component
         * @return reference to this
         */
        template <typename T, typename Func, typename... Args>
        [[nodiscard]] EntityBuilder &with_component_using_function(Func func, Args &&...args)
        {
            static_assert(std::is_invocable_v<Func, T &>, "Func must be invocable with T &");
            auto &component = registry_->get_or_emplace<T>(entity_, std::forward<Args>(args)...);
            func(component);

            registry_->patch<T>(entity_);

            return *this;
        }

        /**
         * Sets the tag to the entity
         * @param tag tag to assign
         * @return self
         */
        EntityBuilder &with_tag(std::string_view tag)
        {
            auto &tag_component = registry_->get<missileengine::TagComponent>(entity_);
            tag_component.tag   = tag;
            return *this;
        }

        /**
         * @brief Removes a component from the entity
         * @tparam T type of component
         * @return The created entity
         */
        entt::entity build()
        {
            has_been_built_ = true;
            return entity_;
        }
    };
} // namespace missileengine
