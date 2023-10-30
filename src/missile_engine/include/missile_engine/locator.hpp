#pragma once

#include "common.hpp"
#include <any>
#include <entt/core/type_info.hpp>
#include <optional>
#include <unordered_map>

namespace missileengine
{
    /**
     * Locator is a class that allows for easy access to services and other objects. (DI container)
     *
     * You can insert multiple instances of the same type, but you will have to specify the type when getting the
     * service.
     */
    class Locator
    {
    private:
        struct Service
        {
            std::size_t name_hash;
            std::any    service;
        };
        std::unordered_multimap<entt::id_type, Service> services_;

    public:
        Locator()                           = default;
        Locator(const Locator &)            = delete;
        Locator(Locator &&)                 = default;
        Locator &operator=(const Locator &) = delete;
        Locator &operator=(Locator &&)      = default;
        ~Locator()                          = default;

        /**
         * Constructs a service in-place in the locator.
         * @tparam T The type of the service.
         * @tparam Args The types of the arguments to pass to the service's constructor.
         * @param args The arguments to pass to the service's constructor.
         * @return True if the service was inserted, false if a service of the same type already exists.
         */
        template <class T, class... Args>
        bool emplace(Args &&...args)
        {
            return emplace_named<T>("", std::forward<T>(args)...);
        }

        /**
         * Constructs a service in-place in the locator.
         * @tparam T The type of the service.
         * @tparam Args The types of the arguments to pass to the service's constructor.
         * @param name The name of the service.
         * @param args The arguments to pass to the service's constructor.
         * @return True if the service was inserted, false if a service of the same type already exists.
         */
        template <class T, class... Args>
        bool emplace_named(std::string_view name, Args &&...args)
        {
            const auto hash      = entt::type_id<T>().hash();
            auto       range     = services_.equal_range(hash);
            auto       name_hash = std::hash<std::string_view>{}(name);

            for (auto it = range.first; it != range.second; ++it)
            {
                if (it->second.name_hash == name_hash)
                {
                    return false;
                }
            }
            services_.emplace(hash, Service{name_hash, std::make_shared<T>(std::forward<Args>(args)...)});
            return true;
        }

        /**
         * Get a service from the locator.
         * @tparam T The type of the service.
         * @return The service.
         */
        template <class T>
        std::optional<std::reference_wrapper<T>> get()
        {
            return get<T>("");
        }

        /**
         * Get a service from the locator.
         * @tparam T The type of the service.
         * @return The service.
         */
        template <class T>
        std::optional<const std::reference_wrapper<T>> get() const
        {
            return get<T>("");
        }

        /**
         * Get a service from the locator.
         * @tparam T The type of the service.
         * @param name The name of the service.
         * @return The service.
         */
        template <class T>
        std::optional<std::reference_wrapper<T>> get(std::string_view name)
        {
            const auto hash  = entt::type_id<T>().hash();
            auto       range = services_.equal_range(hash);

            for (auto it = range.first; it != range.second; ++it)
            {
                if (it->second.name_hash == std::hash<std::string_view>{}(name))
                {
                    auto pointer = std::any_cast<std::shared_ptr<T>>(&it->second.service);
                    return std::ref(**pointer);
                }
            }

            return std::nullopt;
        }

        /**
         * How many services are in the locator.
         * @return how many services are in the locator
         */
        size_t size() const
        {
            return services_.size();
        }

        /**
         * Delete a service from the locator.
         * @tparam T The type of the service.
         * @param name The name of the service.
         */
        template <class T>
        void erase(std::string_view name = "")
        {
            const auto hash  = entt::type_id<T>().hash();
            auto       range = services_.equal_range(hash);
            for (auto it = range.first; it != range.second; ++it)
            {
                if (it->second.name_hash == std::hash<std::string_view>{}(name))
                {
                    services_.erase(it);
                    return;
                }
            }
        }

        /**
         * Delete all services from the locator.
         */
        void clear()
        {
            services_.clear();
        }
    };
} // namespace missileengine
