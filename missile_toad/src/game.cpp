#include "missile_toad/game.hpp"
#include "fmt/format.h"
#include "missile_toad/core/base_system.hpp"
#include "nuklear.h"
#include "raylib-nuklear.h"

extern void register_system(entt::meta_ctx &ctx);

missiletoad::Game::Game(int argc, char **argv)
    : nuklear_context(nullptr, nullptr), argv(argv), argc(argc), debug_mode(true)
{
    // TODO: use argc and argv to select some game options, such as the debug mode. etc.

    spdlog::info("Initializing game.");

    nuklear_context = std::unique_ptr<nk_context, void (*)(nk_context *)>(InitNuklear(12), UnloadNuklear);
    if (nuklear_context == nullptr)
    {
        spdlog::error("Failed to initialize nuklear.");
        throw std::runtime_error("Failed to initialize nuklear.");
    }
    spdlog::trace("Nuklear initialized.");

    // Register Systems meta types.
    register_system(this->systems_meta_ctx);
    spdlog::trace("Systems registered.");

    spdlog::trace("Game::Game() finished.");
}

// TODO: Implement this.
missiletoad::Game::~Game() noexcept = default;

void missiletoad::Game::update(float delta_time) noexcept
{
    spdlog::trace("Game::update() called.");

    unused(delta_time);
    unused(this->argc);
    unused(this->argv);

    // The first step is to update the nuklear context so that it can handle input.
    UpdateNuklear(nuklear_context.get());

    // TODO: Update the scene.

    spdlog::trace("Game::update() finished.");

    if (debug_mode)
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

        DrawNuklear(nuklear_context.get());
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
