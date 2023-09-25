/// @file missile_toad/src/core/game.cpp

#include "missile_toad/core/game.hpp"
#include "missile_toad/core/asset_manager.hpp"
#include "missile_toad/core/base_system.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include "missile_toad/core/game_descriptor.hpp"
#include "missile_toad/core/input_manager.hpp"
#include "missile_toad/core/scene_manager.hpp"

#include <fstream>
#include <nuklear.h>
#include <raylib-nuklear.h>

extern void register_system(entt::meta_ctx &ctx);
extern void register_components(entt::meta_ctx &ctx);

// NOLINTNEXTLINE(*-avoid-non-const-global-variables)
static missiletoad::core::Game *INSTANCE = nullptr;

missiletoad::core::Game::Game(std::vector<std::string_view> &&arguments, const GameDescriptor &game_descriptor)
    : nuklear_context_(nullptr, nullptr), debug_mode_(true)
{
    auto args = std::move(arguments);
    if (INSTANCE != nullptr)
    {
        spdlog::error("Game instance already exists.");
        throw std::runtime_error("Game instance already exists.");
    }
    // TODO: use argc and argv to select some game options, such as the debug mode. etc.

    spdlog::info("Initializing game {}.", game_descriptor.name);

    spdlog::info("Creating window.");
    if (args.size() != 1 || args[0] != "TEST_CASE")
    {
        window_.Init(1280, 720, game_descriptor.name);
    }

    spdlog::info("Window initialized.");

    nuklear_context_ = std::unique_ptr<nk_context, void (*)(nk_context *)>(InitNuklear(12), UnloadNuklear);
    if (nuklear_context_ == nullptr)
    {
        spdlog::error("Failed to initialize nuklear.");
        throw std::runtime_error("Failed to initialize nuklear.");
    }
    spdlog::trace("Nuklear initialized.");

    asset_manager_ = std::make_unique<core::AssetManager>();
    scene_manager_ = std::make_unique<core::SceneManager>(*this);
    input_manager_ = std::make_unique<core::InputManager>();

    // Append asset folder paths to the asset manager.
    for (const auto &asset_folder : game_descriptor.assets_folders)
    {
        asset_manager_->push_asset_folder(asset_folder.path, asset_folder.mount_point);
    }

    // Register Systems meta types.
    register_system(systems_meta_ctx_);
    register_components(components_meta_ctx_);
    spdlog::trace("Systems registered.");

    INSTANCE = this;

    spdlog::trace("Game::Game() finished.");
}

// TODO: Implement this.
missiletoad::core::Game::~Game() noexcept
{
    INSTANCE = nullptr;
}

void missiletoad::core::Game::update(float delta_time) noexcept
{
    spdlog::trace("Game::update() called.");

    input_manager_->update();
    // The first step is to update the nuklear context so that it can handle input.
    UpdateNuklear(nuklear_context_.get());

    if (scene_manager_->active_scene() != nullptr)
    {
        scene_manager_->active_scene()->update(delta_time);
    }

    spdlog::trace("Game::update() finished.");

    if (debug_mode_)
    {
        this->debug_gui();
    }
}

void missiletoad::core::Game::fixed_update(float delta_time) noexcept
{
    spdlog::trace("Game::fixed_update() called.");
    if (scene_manager_->active_scene() != nullptr)
    {
        scene_manager_->active_scene()->fixed_update(delta_time);
    }

    spdlog::trace("Game::fixed_update() finished.");
}

void missiletoad::core::Game::render() noexcept
{
    spdlog::trace("Game::render() called.");
    BeginDrawing();
    {
        ClearBackground(BLACK);

        if (scene_manager_->active_scene() != nullptr)
        {
            scene_manager_->active_scene()->on_render();
        }

        DrawNuklear(nuklear_context_.get());
    }
    EndDrawing();
    spdlog::trace("Game::render() finished.");
}

void missiletoad::core::Game::debug_gui() noexcept
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

void missiletoad::core::Game::run() noexcept
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
void missiletoad::core::Game::close() noexcept
{
    spdlog::trace("Game::close() called.");
    window_.Close();
    spdlog::trace("Game::close() finished.");
}

missiletoad::core::Game &missiletoad::core::Game::get_instance() noexcept
{
    assert(INSTANCE != nullptr);
    return *INSTANCE;
}

missiletoad::core::AssetManager &missiletoad::core::Game::asset_manager() noexcept
{
    return *asset_manager_;
}

missiletoad::core::SceneManager &missiletoad::core::Game::scene_manager() noexcept
{
    return *scene_manager_;
}

missiletoad::core::InputManager &missiletoad::core::Game::input_manager() noexcept
{
    return *input_manager_;
}

missiletoad::core::Scene &missiletoad::core::Game::active_scene() noexcept
{
    return *scene_manager_->active_scene();
}
