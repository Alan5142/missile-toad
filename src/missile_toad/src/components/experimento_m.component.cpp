
#include "missile_toad/components/experimento_m.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::ExperimentoMComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::ExperimentoMComponent>(ctx).type("missiletoad::ExperimentoMComponent"_hs).ctor<>();
}
