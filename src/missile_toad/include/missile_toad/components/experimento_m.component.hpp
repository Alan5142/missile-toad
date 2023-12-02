#pragma once
#include "missile_engine/common.hpp"

#include <boost/sml.hpp>
#include <entt/meta/meta.hpp>

namespace missiletoad
{
    struct ExperimentoMDeathEvent
    {
    };

    struct ExperimentoMIdleEvent
    {
    };

    struct ExperimentoMMoveEvent
    {
    };

    struct ExperimentoAttackEvent
    {
    };

    struct ExperimentoMState
    {
        auto operator()() const
        {
            using namespace boost::sml;
            return make_transition_table(*"initial"_s                               = "follow"_s,
                                         "idle"_s + event<ExperimentoMMoveEvent>    = "follow"_s,
                                         "follow"_s + event<ExperimentoMIdleEvent>  = "idle"_s,
                                         "idle"_s + event<ExperimentoMMoveEvent>    = "death"_s,
                                         "follow"_s + event<ExperimentoMDeathEvent> = "death"_s,
                                         "follow"_s + event<ExperimentoAttackEvent> = "attack"_s,
                                         "attack"_s + event<ExperimentoMIdleEvent>  = "idle"_s,
                                         "attack"_s + event<ExperimentoMDeathEvent> = "death"_s);
        }
    };

    class ExperimentoMComponent
    {
    public:
        static void register_component(entt::meta_ctx &ctx);

        float enemy_speed = 2.8F;

        boost::sml::sm<ExperimentoMState> state_machine;
    };
} // namespace missiletoad
