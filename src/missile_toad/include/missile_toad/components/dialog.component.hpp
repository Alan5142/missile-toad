#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>

namespace missiletoad
{
    class DialogComponent
    {
        int  dialog_id           = 0;
        int  total_dialogs       = 0;
        bool is_dialog_active    = false;
        bool is_dialog_finished  = false;
        bool is_dialog_skippable = false;

    public:
        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad
