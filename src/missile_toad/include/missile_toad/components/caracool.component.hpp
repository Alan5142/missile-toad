#pragma once
#include "missile_engine/common.hpp"

#include <boost/sml.hpp>
#include <entt/meta/meta.hpp>

namespace missiletoad
{

    struct CaracoolStateDeathEvent
    {
    };

    struct CaracoolStateHideEvent
    {
    };

    struct CaracoolStateUnhideEvent
    {
    };

    struct CaracoolStateMoveEvent
    {
    };

    struct CaracoolStateAttackEvent
    {
    };

    struct CaracoolState
    {
        auto operator()() const
        {
            using namespace boost::sml;
            return make_transition_table(*"initial"_s                                 = "follow"_s,
                                         "follow"_s + event<CaracoolStateHideEvent>   = "hide"_s,
                                         "follow"_s + event<CaracoolStateDeathEvent>  = "death"_s,
                                         "hide"_s + event<CaracoolStateAttackEvent>   = "attack"_s,
                                         "attack"_s + event<CaracoolStateUnhideEvent> = "unhide"_s,
                                         "unhide"_s + event<CaracoolStateMoveEvent>   = "follow"_s);
        }
    };

    class CaracoolComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        float enemy_speed = 0.8F;

        boost::sml::sm<CaracoolState> state_machine;
    };
} // namespace missiletoad
