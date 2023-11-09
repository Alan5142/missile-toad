
#include "missile_toad/systems/camera.system.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"
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

        const float x_new = std::lerp(transform_component.position.x, x_target, follow_speed);
        const float y_new = std::lerp(transform_component.position.y, y_target, follow_speed);

        transform_component.position = glm::vec2{x_new, y_new};
    }
}
