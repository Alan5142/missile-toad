/// @file missile_toad/src/game.cpp

#include "missile_toad/game.hpp"
#include "missile_toad/core/asset_manager.hpp"
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include "missile_toad/core/game_descriptor.hpp"

#include <entt/locator/locator.hpp>
#include <fstream>
#include <nuklear.h>
#include <raylib-nuklear.h>

extern void register_system(entt::meta_ctx &ctx);
extern void register_components(entt::meta_ctx &ctx);

missiletoad::Game::Game(int argc, char **argv)
    : nuklear_context_(nullptr, nullptr), argv_(argv), argc_(argc), debug_mode_(true)
{
    // TODO: use argc and argv to select some game options, such as the debug mode. etc.
    auto game_json = std::ifstream("game.json");
    if (!game_json.is_open())
    {
        spdlog::error("Failed to open game.json.");
        throw std::runtime_error("Failed to open game.json.");
    }
    // Read all contents of the file into a string.
    std::string game_json_str((std::istreambuf_iterator<char>(game_json)), std::istreambuf_iterator<char>());
    auto        game_descriptor = missiletoad::core::load_game_descriptor(game_json_str).value();

    spdlog::info("Initializing game {}.", game_descriptor.name);

    spdlog::info("Creating window.");
    window_.Init(1280, 720, game_descriptor.name);

    spdlog::info("Game initialized.");

    nuklear_context_ = std::unique_ptr<nk_context, void (*)(nk_context *)>(InitNuklear(12), UnloadNuklear);
    if (nuklear_context_ == nullptr)
    {
        spdlog::error("Failed to initialize nuklear.");
        throw std::runtime_error("Failed to initialize nuklear.");
    }
    spdlog::trace("Nuklear initialized.");

    asset_manager_ = std::make_unique<core::AssetManager>();

    // Append asset folder paths to the asset manager.
    for (const auto &asset_folder : game_descriptor.assets_folders)
    {
        asset_manager_->push_asset_folder(asset_folder.path, asset_folder.mount_point);
    }

    spdlog::trace("Registering Game systems in the locator.");
    locator_.emplace<missiletoad::core::AssetManager *>(asset_manager_.get());
    locator_.emplace<missiletoad::Game *>(this);
    locator_.emplace<nk_context *>(nuklear_context_.get());
    spdlog::trace("Game systems registered in the locator.");

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
    try
    {
        // Show FPS and frame time
        const auto fps        = fmt::format("FPS: {}", GetFPS());
        const auto frame_time = fmt::format("Frame time: {:.2f} ms", GetFrameTime() * 1000);
        DrawText(fps.c_str(), 0, 0, 20, RED);
        DrawText(frame_time.c_str(), 150, 0, 20, RED);
    }
    catch (const std::exception &e)
    {
        spdlog::error("{}", e.what());
    }
}

void missiletoad::Game::run() noexcept
{
    auto current_time = std::chrono::high_resolution_clock::now();
    auto accumulator  = std::chrono::duration<float>(0);

    while (!window_.ShouldClose())
    {
        auto new_time   = std::chrono::high_resolution_clock::now();
        auto frame_time = new_time - current_time;
        current_time    = new_time;
        accumulator += frame_time;

        // We do this to guarantee that the fixed update is called at a fixed rate.
        // For instance, if the game is running at 60 FPS, and the fixed update rate is 30 FPS,
        // then the fixed update will be called every 2 frames.
        // But if the game is running at 30 FPS, then the fixed update will be called every frame.
        // To achieve this, we accumulate the time between frames, and call the fixed update
        // as many times as needed.
        while (accumulator >= std::chrono::duration<float>(missiletoad::core::UPDATE_RATE))
        {
            // FixedTick
            this->fixed_update(missiletoad::core::UPDATE_RATE);
            accumulator -= std::chrono::duration<float>(missiletoad::core::UPDATE_RATE);
        }

        // Tick
        auto delta_time = std::chrono::duration<float>(frame_time).count();
        this->update(delta_time);

        // Render
        this->render();
    }
}
void missiletoad::Game::close() noexcept
{
    spdlog::trace("Game::close() called.");
    window_.Close();
    spdlog::trace("Game::close() finished.");
}
