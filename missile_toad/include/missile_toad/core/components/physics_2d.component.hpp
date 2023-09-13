#pragma once
#include "missile_toad/core/common.hpp"

#include <box2d/box2d.h>
#include <entt/meta/meta.hpp>

namespace missiletoad::core
{
    class Physics2dComponent
    {
    private:
        b2Body    *body_;
        b2Fixture *fixture_;
        bool       is_static_;
        bool       is_collidable_;

    public:
        Physics2dComponent();

        static void register_component(entt::meta_ctx &ctx);

        void set_static(bool is_static);
        void set_collidable(bool is_collidable);
        void set_position(float x, float y);
        void set_rotation(float angle);
        void set_linear_velocity(float x, float y);

        void apply_force(float x, float y);
        void apply_force_to_center(float x, float y);
        void apply_torque(float torque);
        void apply_linear_impulse(float x, float y);
        void apply_linear_impulse_to_center(float x, float y);

        b2Body *get_body()
        {
            return body_;
        }

        [[nodiscard]] b2Body *get_body() const
        {
            return body_;
        }

        [[nodiscard]] b2Fixture *get_fixture() const
        {
            return fixture_;
        }

        [[nodiscard]] bool is_static() const
        {
            return is_static_;
        }

        [[nodiscard]] bool is_collidable() const
        {
            return is_collidable_;
        }
    };
} // namespace missiletoad::core
