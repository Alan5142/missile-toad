
#include "missile_toad/systems/main_menu.system.hpp"
#include "missile_engine/core_components.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <missile_engine/asset_manager.hpp>
#include <missile_engine/scene_manager.hpp>

missiletoad::MainMenuSystem::MainMenuSystem(missileengine::Game *game)
{
    unused(game);

    auto &scene = game->active_scene();

    scene.create_entity()
        .with_component<missileengine::TransformComponent>()
        .with_component_using_function<missileengine::Camera2dComponent>(
            [&](auto &camera)
            {
                camera.set_zoom(1.0F);
                camera.set_offset(
                    {static_cast<float>(GetScreenWidth()) / 2.0F, static_cast<float>(GetScreenHeight()) / 2.0F});
                camera.set_is_main_camera(true);
            },
            glm::vec2{static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())})
        .build();

    auto music = game->asset_manager().load<missileengine::Music>("/assets/sounds/frog_jump.mp3");
    music->get_music().Play();
    music->get_music().SetVolume(0.1F);

    auto movie = game->asset_manager().load<missileengine::Movie>("/assets/videos/frog_jump.mpg");

    scene.create_entity()
        .with_component_using_function<missileengine::TransformComponent>(
            [&](missileengine::TransformComponent &transform)
            {
                transform.position = {-2.0F, 3.0F};
                transform.scale    = {8.0F, 8.0F};
            })
        .with_component_using_function<missileengine::MoviePlayerComponent>(
            [&](auto &movie_component)
            {
                movie_component.movie->play(); //
            },
            movie)
        .with_component<missileengine::AudioComponent>(music)
        .build();
}

void missiletoad::MainMenuSystem::on_update(float delta_time)
{
    unused(delta_time);
    auto &game            = missileengine::Game::get_instance();
    auto *nuklear_context = game.get_instance().nuklear_context();

    // Create a window to cover all of the screen
    if (nk_begin(nuklear_context, "Main Menu", nk_rect(500, 300, 300, 300), NK_WINDOW_NO_SCROLLBAR) == 1)
    {
        // Create a column for the buttons
        nk_layout_row_dynamic(nuklear_context, 50, 1);
        if (nk_button_label(nuklear_context, "Play") == 1)
        {
            game.scene_manager().load_scene("/assets/levels/scene.json");
        }
    }
    nk_end(nuklear_context);
}

void missiletoad::MainMenuSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::MainMenuSystem>(ctx)
        .type("missiletoad::MainMenuSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
}
