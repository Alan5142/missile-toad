#pragma once
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/common.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>
#include <gsl/gsl>

namespace missiletoad::core
{
    class RendererSystem : public missiletoad::core::BaseSystem
    {
        entt::registry &registry_;

    public:
        RendererSystem();
        static void register_system(entt::meta_ctx &ctx);

        void on_render() override;
    };
} // namespace missiletoad::core
