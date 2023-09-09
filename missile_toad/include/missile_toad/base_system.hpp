#pragma once
#include "missile_toad/common.hpp"

namespace missiletoad
{
    class BaseSystem
    {
    public:
        virtual ~BaseSystem() = default;

        BaseSystem()                              = default;
        BaseSystem(const BaseSystem &)            = delete;
        BaseSystem(BaseSystem &&)                 = delete;
        BaseSystem &operator=(const BaseSystem &) = delete;
        BaseSystem &operator=(BaseSystem &&)      = delete;

        virtual void on_start()
        {
        }

        virtual void on_update(float delta_time)
        {
            unused(delta_time);
        }

        virtual void on_fixed_update(float delta_time)
        {
            unused(delta_time);
        }

        virtual void on_destroy()
        {
        }

        virtual void on_render()
        {
        }
    };
} // namespace missiletoad
