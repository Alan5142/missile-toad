#include "missile_toad/game.hpp"
#include "fmt/format.h"
#include "missile_toad/core/asset_manager.hpp"
#include "missile_toad/core/base_system.hpp"
#include "nuklear.h"
#include "raylib-nuklear.h"

#include <entt/locator/locator.hpp>

extern void register_system(entt::meta_ctx &ctx);

static entt::resource<missiletoad::core::Texture> MISSILE_TOAD; // NOLINT(*-avoid-non-const-global-variables)

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

    MISSILE_TOAD = asset_manager_->load<core::Texture>("/assets/textures/missiletoad.png");

    // Register Systems meta types.
    register_system(systems_meta_ctx_);
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

    // TODO: Update the scene.

    spdlog::trace("Game::update() finished.");

    if (debug_mode_)
    {
        this->debug_gui();
    }
}

void missiletoad::Game::fixed_update(float /*delta_time*/) noexcept
{
    spdlog::trace("Game::fixed_update() called.");
    // TODO: Update the scene.
    unused(this);

    spdlog::trace("Game::fixed_update() finished.");
}

void missiletoad::Game::render() noexcept
{
    spdlog::trace("Game::render() called.");
    // TODO: Implement this.
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        // TODO: Update the scene.
        // this->current_scene->render();

        ::DrawTexture(MISSILE_TOAD->get_texture(), 0, 0, WHITE);

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
