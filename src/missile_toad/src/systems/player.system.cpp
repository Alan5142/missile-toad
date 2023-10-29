
#include "missile_toad/systems/player.system.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/player.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void configure_player_axis(missilengine::Game *game)
{
    using missilengine::Action;
    using missilengine::EKey;
    const auto move_y_axis = missilengine::Axis{
        missilengine::AxisButton{EKey::S, EKey::W},
    };

    const auto move_y_gamepad_axis = missilengine::Axis{missilengine::GamepadAxisData{
        missilengine::EGamepadAxis::LEFT_Y,
        0,
    }};

    const auto move_x_axis = missilengine::Axis{
        missilengine::AxisButton{EKey::D, EKey::A},
    };

    const auto move_x_gamepad_axis = missilengine::Axis{missilengine::GamepadAxisData{
        missilengine::EGamepadAxis::LEFT_X,
        0,
    }};

    game->input_manager().add_axis("move_y", move_y_axis);
    game->input_manager().add_axis("move_y", move_y_gamepad_axis);

    game->input_manager().add_axis("move_x", move_x_axis);
    game->input_manager().add_axis("move_x", move_x_gamepad_axis);
}

missiletoad::PlayerSystem::PlayerSystem(missilengine::Game *game)
{
    using missilengine::Action;
    using missilengine::EKey;
    using missilengine::GamepadAxisData;

    configure_player_axis(game);
}

void missiletoad::PlayerSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::PlayerSystem>(ctx)
        .type("missiletoad::PlayerSystem"_hs)
        .base<missilengine::BaseSystem>()
        .ctor<missilengine::Game *>();
    // TODO: Add your register code here
}

void missiletoad::PlayerSystem::on_update(float delta_time)
{
    unused(delta_time);
    auto &game           = missilengine::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto &input_manager  = game.input_manager();

    auto view = scene_entities.view<missiletoad::PlayerComponent>();
    for (auto entity : view)
    {
        auto &rigidbody = scene_entities.get<missilengine::Rigidbody2dComponent>(entity);
        auto &transform = scene_entities.get<missilengine::TransformComponent>(entity);

        unused(transform);

        auto move_x = input_manager.get_axis("move_x");
        auto move_y = input_manager.get_axis("move_y");

        if (move_x != 0.0F || move_y != 0.0F)
        {
            spdlog::info("Player moving: ({}, {})", move_x, move_y);
        }
        rigidbody.set_linear_velocity({move_x, move_y});
    }
}
