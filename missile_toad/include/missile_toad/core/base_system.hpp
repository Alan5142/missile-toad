#pragma once
#include "common.hpp"

namespace missiletoad::core
{
    /**
     * A base class for all systems.
     * It provides empty implementations for all the virtual functions.
     * This is useful for systems that don't need to implement all the functions.
     */
    class BaseSystem
    {
    public:
        /**
         * Virtual destructor to allow for polymorphism.
         */
        virtual ~BaseSystem() = default;

        /**
         * Default constructor.
         */
        BaseSystem()                              = default;
        BaseSystem(const BaseSystem &)            = delete;
        BaseSystem(BaseSystem &&)                 = delete;
        BaseSystem &operator=(const BaseSystem &) = delete;
        BaseSystem &operator=(BaseSystem &&)      = delete;

        /**
         * Called when the system is started.
         * A system is started when it is added to the scene.
         * This is useful for initializing variables inside the system.
         * @note This is called right _before_ the first update.
         */
        virtual void on_start()
        {
        }

        /**
         * Called when the system is updated.
         * This is useful for updating variables inside the system.
         * @note This is called after the fixed update.
         * @param delta_time the time since the last update
         */
        virtual void on_update(float delta_time)
        {
            unused(delta_time);
        }

        /**
         * Called when the system is fixed updated.
         * This is useful for performing physic-related calculations and movement.
         * @note This is called before the update.
         * @param delta_time
         */
        virtual void on_fixed_update(float delta_time)
        {
            unused(delta_time);
        }

        /**
         * Called when the system is destroyed.
         * A system is destroyed when it is removed from the scene.
         * Usually when the scene is destroyed.
         */
        virtual void on_destroy()
        {
        }

        /**
         * Called when the system is rendered.
         * This is where rendering-related code should go.
         * @note This is called after the update and before the next frame is started.
         */
        virtual void on_render()
        {
        }
    };
} // namespace missiletoad::core
