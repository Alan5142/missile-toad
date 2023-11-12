
#include "missile_toad/systems/player.system.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_toad/components/player.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <string>

void configure_player_axis(missileengine::Game *game)
{
    using missileengine::Action;
    using missileengine::EKey;
    const auto move_y_axis = missileengine::Axis{
        missileengine::AxisButton{EKey::S, EKey::W},
    };

    const auto move_y_gamepad_axis = missileengine::Axis{missileengine::GamepadAxisData{
        missileengine::EGamepadAxis::LEFT_Y,
        0,
    }};

    const auto move_x_axis = missileengine::Axis{
        missileengine::AxisButton{EKey::D, EKey::A},
    };

    const auto move_x_gamepad_axis = missileengine::Axis{missileengine::GamepadAxisData{
        missileengine::EGamepadAxis::LEFT_X,
        0,
    }};

    game->input_manager().add_axis("move_y", move_y_axis);
    game->input_manager().add_axis("move_y", move_y_gamepad_axis);

    game->input_manager().add_axis("move_x", move_x_axis);
    game->input_manager().add_axis("move_x", move_x_gamepad_axis);
}

missiletoad::PlayerSystem::PlayerSystem(missileengine::Game *game)
{
    using missileengine::Action;
    using missileengine::EKey;
    using missileengine::GamepadAxisData;

    configure_player_axis(game);
}

void missiletoad::PlayerSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::PlayerSystem>(ctx)
        .type("missiletoad::PlayerSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
    // TODO: Add your register code here
}

void missiletoad::PlayerSystem::on_update(float delta_time)
{
    unused(delta_time);
    auto &game           = missileengine::Game::get_instance();
    auto &scene_entities = game.active_scene().get_registry();
    auto &input_manager  = game.input_manager();
    auto  mouse_position = input_manager.get_mouse_position();

    auto view = scene_entities.view<missiletoad::PlayerComponent>();
    for (auto entity : view)
    {
        auto &rigidbody     = scene_entities.get<missileengine::Rigidbody2dComponent>(entity);
        auto &player        = scene_entities.get<missiletoad::PlayerComponent>(entity);
        auto &line_renderer = scene_entities.get<missileengine::LineRendererComponent>(entity);
            
        auto move_x  = input_manager.get_axis("move_x");
        auto move_y  = input_manager.get_axis("move_y");
        auto mouse_x = mouse_position.x;
        auto mouse_y = mouse_position.y;
        auto position = rigidbody.get_body()->GetPosition();
        auto position_x = position.x * 64;
        auto position_y = position.y * 64;

        spdlog::info("frog: {} {} mouse: {} {}", position_x, position_y, mouse_x, mouse_y);

        line_renderer.start = {position_x, position_y};
        line_renderer.end   = {mouse_x, mouse_y};

        DrawLine(position_x, position_y, mouse_x, mouse_y, GREEN);

        rigidbody.set_linear_velocity({move_x * player.player_speed, move_y * player.player_speed});
    }
}
