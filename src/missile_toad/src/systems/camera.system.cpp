
#include "missile_toad/systems/camera.system.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/physics_utils.hpp"
#include "missile_toad/components/better_camera.component.hpp"
#include "missile_toad/components/player.component.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missiletoad::CameraSystem::CameraSystem(missileengine::Game *game)
{
    unused(game);
}

void missiletoad::CameraSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::CameraSystem>(ctx)
        .type("missiletoad::CameraSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
}

bool hit_raycast(const glm::vec2 &start, const glm::vec2 &end, float distance)
{
    if (auto raycast = missileengine::Physics::raycast(start, end, distance); raycast.has_value())
    {
        auto &result = raycast.value();
        if (auto *tag =
                missileengine::Game::get_instance().active_scene().try_get_component<missileengine::TagComponent>(
                    result.entity);
            tag && tag->tag == "Room")
        {
            return true;
        }
    }
    return false;
}

constexpr auto Y_RAYCAST_DISTANCE = 2.3F;
constexpr auto X_RAYCAST_DISTANCE = 5.3F;

constexpr auto Y_RAYCAST_EXIT_DISTANCE = 4.0F;
constexpr auto X_RAYCAST_EXIT_DISTANCE = 7.0F;

void lock_target(bool is_hitting_1, bool is_hitting_2, bool is_hitting_exit_1, bool is_hitting_exit_2, bool &is_locked)
{
    if (is_hitting_1 || is_hitting_2 || is_locked)
    {
        is_locked = (is_hitting_exit_1 || is_hitting_exit_2);
    }
}

void missiletoad::CameraSystem::on_update(float delta_time)
{
    auto                              &game             = missileengine::Game::get_instance();
    auto                              &scene            = game.active_scene();
    missileengine::TransformComponent *player_transform = nullptr;

    unused(delta_time);

    auto player_view = scene.view<missiletoad::PlayerComponent, missileengine::TransformComponent>();
    for (auto entity : player_view)
    {
        player_transform = &player_view.get<missileengine::TransformComponent>(entity);
    }

    auto view = scene.view<missileengine::Camera2dComponent, missiletoad::BetterCameraComponent,
                           missileengine::TransformComponent>();
    for (auto entity : view)
    {
        auto &transform_component     = view.get<missileengine::TransformComponent>(entity);
        auto &better_camera_component = view.get<missiletoad::BetterCameraComponent>(entity);

        const float x_target = player_transform->position.x + better_camera_component.x_offset;
        const float y_target = player_transform->position.y + better_camera_component.y_offset;

        const float follow_speed = delta_time * (better_camera_component.follow_speed);

        const auto is_up_hitting =
            hit_raycast(player_transform->position, missileengine::Physics::UP, Y_RAYCAST_DISTANCE);
        const auto is_down_hitting =
            hit_raycast(player_transform->position, missileengine::Physics::DOWN, Y_RAYCAST_DISTANCE);
        const auto is_left_hitting =
            hit_raycast(player_transform->position, missileengine::Physics::LEFT, X_RAYCAST_DISTANCE);
        const auto is_right_hitting =
            hit_raycast(player_transform->position, missileengine::Physics::RIGHT, X_RAYCAST_DISTANCE);

        const auto is_up_hitting_exit =
            hit_raycast(player_transform->position, missileengine::Physics::UP, Y_RAYCAST_EXIT_DISTANCE);
        const auto is_down_hitting_exit =
            hit_raycast(player_transform->position, missileengine::Physics::DOWN, Y_RAYCAST_EXIT_DISTANCE);
        const auto is_left_hitting_exit =
            hit_raycast(player_transform->position, missileengine::Physics::LEFT, X_RAYCAST_EXIT_DISTANCE);
        const auto is_right_hitting_exit =
            hit_raycast(player_transform->position, missileengine::Physics::RIGHT, X_RAYCAST_EXIT_DISTANCE);

        lock_target(is_up_hitting, is_down_hitting, is_up_hitting_exit, is_down_hitting_exit,
                    better_camera_component.is_y_locked);
        lock_target(is_left_hitting, is_right_hitting, is_left_hitting_exit, is_right_hitting_exit,
                    better_camera_component.is_x_locked);

        auto x_new = transform_component.position.x;
        if (!better_camera_component.is_x_locked)
        {
            x_new = std::lerp(transform_component.position.x, x_target, follow_speed);
        }

        auto y_new = transform_component.position.y;
        if (!better_camera_component.is_y_locked)
        {
            y_new = std::lerp(transform_component.position.y, y_target, follow_speed);
        }

        transform_component.position = glm::vec2{x_new, y_new};
    }
}
