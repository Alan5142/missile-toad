#pragma once
#include "missile_engine/common.hpp"

#include <boost/sml.hpp>
#include <entt/meta/meta.hpp>

namespace missiletoad
{
    struct MechaMoscaDeathEvent
    {
    };

    struct MechaMoscaState
    {
        auto operator()() const
        {
            using namespace boost::sml;
            return make_transition_table(*"initial"_s                             = "follow"_s,
                                         "follow"_s + event<MechaMoscaDeathEvent> = "death"_s);
        }
    };

    class MechaMoscaComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        float enemy_speed = 1.2F;

        boost::sml::sm<MechaMoscaState> state_machine;
    };
} // namespace missiletoad
