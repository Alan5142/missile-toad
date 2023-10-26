
#include "missile_toad/game/systems/player.system.hpp"
#include "missile_toad/core/core_components.hpp"
#include "missile_toad/core/game.hpp"
#include "missile_toad/core/input_manager.hpp"
#include "missile_toad/game/components/player.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void configure_player_axis(missiletoad::core::Game *game)
{
    using missiletoad::core::Action;
    using missiletoad::core::EKey;
    const auto move_y_axis = missiletoad::core::Axis{
        missiletoad::core::AxisButton{EKey::S, EKey::W},
    };

    const auto move_y_gamepad_axis = missiletoad::core::Axis{missiletoad::core::GamepadAxisData{
        missiletoad::core::EGamepadAxis::LEFT_Y,
        0,
    }};

    const auto move_x_axis = missiletoad::core::Axis{
        missiletoad::core::AxisButton{EKey::D, EKey::A},
    };

    const auto move_x_gamepad_axis = missiletoad::core::Axis{missiletoad::core::GamepadAxisData{
        missiletoad::core::EGamepadAxis::LEFT_X,
        0,
    }};

    game->input_manager().add_axis("move_y", move_y_axis);
    game->input_manager().add_axis("move_y", move_y_gamepad_axis);

    game->input_manager().add_axis("move_x", move_x_axis);
    game->input_manager().add_axis("move_x", move_x_gamepad_axis);
}

missiletoad::game::PlayerSystem::PlayerSystem(missiletoad::core::Game *game)
{
    using missiletoad::core::Action;
    using missiletoad::core::EKey;
    using missiletoad::core::GamepadAxisData;

    configure_player_axis(game);
}

void missiletoad::game::PlayerSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::game::PlayerSystem>(ctx)
        .type("missiletoad::game::PlayerSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<missiletoad::core::Game *>();
    // TODO: Add your register code here
}

void missiletoad::game::PlayerSystem::on_update(float delta_time)
{
    unused(delta_time);
    auto &game           = missiletoad::core::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto &input_manager  = game.input_manager();

    auto view = scene_entities.view<missiletoad::game::PlayerComponent>();
    for (auto entity : view)
    {
        auto &rigidbody = scene_entities.get<missiletoad::core::Rigidbody2dComponent>(entity);

        auto move_x = input_manager.get_axis("move_x");
        auto move_y = input_manager.get_axis("move_y");

        if (move_x != 0.0F || move_y != 0.0F)
        {
            spdlog::info("Player moving: ({}, {})", move_x, move_y);
        }
        rigidbody.set_linear_velocity({move_x, move_y});
    }
}
