
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/common.hpp"

#include <entt/meta/meta.hpp>

namespace core
{
    class RendererSystem : public missiletoad::core::BaseSystem
    {
    public:
        static void register_system(entt::meta_ctx &ctx);

        void on_render() override;
    };
} // namespace core
