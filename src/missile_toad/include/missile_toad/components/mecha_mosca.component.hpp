#pragma once
#include "missile_engine/common.hpp"

#include <boost/sml.hpp>
#include <entt/meta/meta.hpp>

namespace missiletoad
{
    struct DamageEvent
    {
        bool is_dead = false;
    };

    struct MechaMoscaState
    {
        auto operator()() const
        {
            using namespace boost::sml;
            constexpr auto is_dead = [](const auto &event)
            {
                return event.is_dead;
            };
            return make_transition_table(*"initial"_s                             = "follow"_s,
                                         "follow"_s + event<DamageEvent>[is_dead] = "dead"_s);
        }
    };

    class MechaMoscaComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        float enemy_speed = 2.4F;

        boost::sml::sm<MechaMoscaState> state_machine;
    };
} // namespace missiletoad
