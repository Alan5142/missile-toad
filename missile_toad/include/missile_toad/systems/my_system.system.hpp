
#include "missile_toad/base_system.hpp"
#include "missile_toad/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class MySystemSystem : public missiletoad::BaseSystem
    {
    public:
        static void register_system(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
