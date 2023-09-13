#include "missile_toad/game.hpp"
#include "fmt/format.h"
#include "missile_toad/core/asset_manager.hpp"
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/components/camera_2d.component.hpp"
#include "missile_toad/core/components/physics_2d.component.hpp"
#include "missile_toad/core/components/sprite.component.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include "missile_toad/core/systems/physics.system.hpp"
#include "missile_toad/core/systems/renderer.system.hpp"
#include "nuklear.h"
#include "raylib-nuklear.h"

#include <entt/locator/locator.hpp>

extern void register_system(entt::meta_ctx &ctx);
extern void register_components(entt::meta_ctx &ctx);

missiletoad::Game::Game(int argc, char **argv)
    : nuklear_context_(nullptr, nullptr), argv_(argv), argc_(argc), debug_mode_(true)
{
    // TODO: use argc and argv to select some game options, such as the debug mode. etc.

    spdlog::info("Initializing game.");

    nuklear_context_ = std::unique_ptr<nk_context, void (*)(nk_context *)>(InitNuklear(12), UnloadNuklear);
    if (nuklear_context_ == nullptr)
    {
        spdlog::error("Failed to initialize nuklear.");
        throw std::runtime_error("Failed to initialize nuklear.");
    }
    spdlog::trace("Nuklear initialized.");

    asset_manager_ = std::make_unique<core::AssetManager>();
    entt::locator<core::AssetManager *>::emplace(asset_manager_.get());

    auto missile_toad_tex = asset_manager_->load<core::Texture>("/assets/textures/missiletoad.png");

    scene_ = std::make_unique<missiletoad::core::Scene>();

    scene_->add_system<core::RendererSystem>();
    scene_->add_system<core::PhysicsSystem>();

    auto &registry = scene_->get_registry();

    auto missile_toad_entity = registry.create();

    registry.emplace<core::SpriteComponent>(missile_toad_entity, missile_toad_tex);
    auto transform     = core::TransformComponent{};
    transform.position = {0, 0};
    transform.scale    = {1, 1};
    transform.rotation = 0;
    registry.emplace<core::TransformComponent>(missile_toad_entity, transform);
    auto physics = core::Physics2dComponent{};
    physics.set_static(false);
    physics.set_collidable(true);
    physics.set_position(transform.position.x, transform.position.y);
    registry.emplace<core::Physics2dComponent>(missile_toad_entity, physics);

    // Create a camera
    auto camera_entity = registry.create();
    auto camera        = core::Camera2dComponent{};
    camera.camera      = Camera2D{.offset   = Vector2{GetScreenWidth() / 2.0F, GetScreenHeight() / 2.0F},
                                  .target   = Vector2{0, 0},
                                  .rotation = 0,
                                  .zoom     = 20};
    registry.emplace<core::Camera2dComponent>(camera_entity, camera);
    registry.emplace<core::TransformComponent>(camera_entity, transform);

    // Create a custom box
    auto box_entity        = registry.create();
    auto box_transform     = core::TransformComponent{};
    auto box_physics       = core::Physics2dComponent{};
    box_transform.position = {10, 10};
    box_transform.scale    = {1, 1};
    box_transform.rotation = 0;
    box_physics.set_static(true);
    box_physics.set_collidable(true);
    box_physics.set_position(box_transform.position.x, box_transform.position.y);
    registry.emplace<core::TransformComponent>(box_entity, box_transform);
    registry.emplace<core::Physics2dComponent>(box_entity, box_physics);
    registry.emplace<core::SpriteComponent>(box_entity, missile_toad_tex);

    // Register Systems meta types.
    register_system(systems_meta_ctx_);
    register_components(components_meta_ctx_);
    spdlog::trace("Systems registered.");

    spdlog::trace("Game::Game() finished.");
}

// TODO: Implement this.
missiletoad::Game::~Game() noexcept = default;

void missiletoad::Game::update(float delta_time) noexcept
{
    spdlog::trace("Game::update() called.");

    unused(delta_time);
    unused(this->argc_);
    unused(this->argv_);

    // The first step is to update the nuklear context so that it can handle input.
    UpdateNuklear(nuklear_context_.get());

    if (scene_)
    {
        scene_->update(delta_time);
    }

    spdlog::trace("Game::update() finished.");

    if (debug_mode_)
    {
        this->debug_gui();
    }
}

void missiletoad::Game::fixed_update(float delta_time) noexcept
{
    spdlog::trace("Game::fixed_update() called.");
    if (scene_)
    {
        scene_->fixed_update(delta_time);
    }

    spdlog::trace("Game::fixed_update() finished.");
}

void missiletoad::Game::render() noexcept
{
    spdlog::trace("Game::render() called.");
    // TODO: Implement this.
    BeginDrawing();
    {
        ClearBackground(BLACK);

        if (scene_)
        {
            scene_->on_render();
        }

        DrawNuklear(nuklear_context_.get());
    }
    EndDrawing();
    spdlog::trace("Game::render() finished.");
}

void missiletoad::Game::debug_gui() noexcept
{
    // Show FPS and frame time
    const auto fps        = fmt::format("FPS: {}", GetFPS());
    const auto frame_time = fmt::format("Frame time: {:.2f} ms", GetFrameTime() * 1000);

    DrawText(fps.c_str(), 0, 0, 20, RED);
    DrawText(frame_time.c_str(), 150, 0, 20, RED);
}
