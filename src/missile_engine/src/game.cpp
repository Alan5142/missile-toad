/// @file missile_toad/src/core/game.cpp

#include "missile_engine/game.hpp"
#include "missile_engine/asset_manager.hpp"
#include "missile_engine/base_system.hpp"
#include "missile_engine/components/camera_2d.component.hpp"
#include "missile_engine/components/transform.component.hpp"
#include "missile_engine/game_descriptor.hpp"
#include "missile_engine/input_manager.hpp"
#include "missile_engine/scene_manager.hpp"

#include <fstream>
#include <nuklear.h>
#include <raylib-nuklear.h>

extern void missileengine_register_components(entt::meta_ctx &ctx);
extern void missileengine_register_system(entt::meta_ctx &ctx);

extern void game_register_components(entt::meta_ctx &ctx) WEAK_LINKAGE;
extern void game_register_system(entt::meta_ctx &ctx) WEAK_LINKAGE;

constexpr auto WINDOW_WIDTH  = 1280;
constexpr auto WINDOW_HEIGHT = 720;

constexpr auto NUKLEAR_DEFAULT_FONT_SIZE = 20;

// NOLINTNEXTLINE(*-avoid-non-const-global-variables)
static missileengine::Game *INSTANCE = nullptr;

missileengine::Game::Game(std::vector<std::string_view> &&arguments, const GameDescriptor &game_descriptor)
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

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    spdlog::info("Creating window.");
    if (args.size() != 1 || args[0] != "TEST_CASE")
    {
        window_.Init(WINDOW_WIDTH, WINDOW_HEIGHT, game_descriptor.name);
    }

    spdlog::info("Window initialized.");

    nuklear_context_ =
        std::unique_ptr<nk_context, void (*)(nk_context *)>(InitNuklear(NUKLEAR_DEFAULT_FONT_SIZE), UnloadNuklear);

    if (nuklear_context_ == nullptr)
    {
        spdlog::error("Failed to initialize nuklear.");
        throw std::runtime_error("Failed to initialize nuklear.");
    }
    spdlog::trace("Nuklear initialized.");

    asset_manager_ = std::make_unique<AssetManager>();
    scene_manager_ = std::make_unique<SceneManager>(*this);
    input_manager_ = std::make_unique<InputManager>();

    // Append asset folder paths to the asset manager.
    for (const auto &asset_folder : game_descriptor.assets_folders)
    {
        asset_manager_->push_asset_folder(asset_folder.path, asset_folder.mount_point);
    }

    // Register Systems meta types.
    missileengine_register_system(systems_meta_ctx_);
    missileengine_register_components(components_meta_ctx_);
    game_register_system(systems_meta_ctx_);
    game_register_components(components_meta_ctx_);
    spdlog::trace("Systems registered.");

    INSTANCE = this;

    scene_manager_->load_scene(game_descriptor.default_scene);

    spdlog::trace("Game::Game() finished.");
}

// TODO: Implement this.
missileengine::Game::~Game() noexcept
{
    INSTANCE = nullptr;
}

void missileengine::Game::update(float delta_time) noexcept
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

void missileengine::Game::fixed_update(float delta_time) noexcept
{
    spdlog::trace("Game::fixed_update() called.");
    if (scene_manager_->active_scene() != nullptr)
    {
        scene_manager_->active_scene()->fixed_update(delta_time);
    }

    spdlog::trace("Game::fixed_update() finished.");
}

void missileengine::Game::render() noexcept
{
    spdlog::trace("Game::render() called.");

    if (scene_manager_->active_scene() != nullptr)
    {
        scene_manager_->active_scene()->on_render();

        auto view = scene_manager_->active_scene()->get_registry().view<missileengine::Camera2dComponent>();
        for (auto entity : view)
        {
            auto &camera = view.get<missileengine::Camera2dComponent>(entity);
            if (!camera.is_main_camera())
            {
                continue;
            }

            BeginDrawing();
            ClearBackground(BLACK);
            auto &texture = camera.get_render_texture().texture;
            DrawTextureRec(texture, {0, 0, static_cast<float>(texture.width), -static_cast<float>(texture.height)},
                           {0, 0}, WHITE);
            DrawNuklear(nuklear_context_.get());

            EndDrawing();
        }
        BeginDrawing();
        ClearBackground(BLACK);
    }

    spdlog::trace("Game::render() finished.");
}

void missileengine::Game::debug_gui() noexcept
{
    try
    {
        // Show FPS and frame time
        const auto     fps                  = fmt::format("FPS: {}", GetFPS());
        const auto     frame_time           = fmt::format("Frame time: {:.2f} ms", GetFrameTime() * 1000);
        constexpr auto debug_fps_position_x = 0;
        constexpr auto debug_fps_position_y = 0;
        constexpr auto debug_fps_font_size  = 20;
        constexpr auto debug_fps_width      = 400;
        constexpr auto debug_fps_height     = debug_fps_font_size * 4.0F;

        // Begin a transparent window
        nuklear_context_->style.window.fixed_background = nk_style_item_color(nk_rgba(50, 50, 50, 50));
        if (nk_begin(nuklear_context_.get(), "Debug",
                     nk_rect(debug_fps_position_x, debug_fps_position_y, debug_fps_width, debug_fps_height), 0))
        {
            nk_layout_row_dynamic(nuklear_context_.get(), debug_fps_font_size, 1);
            nk_label_colored(nuklear_context_.get(), fps.c_str(), NK_TEXT_LEFT, nk_rgb(255, 0, 0));
            nk_label_colored(nuklear_context_.get(), frame_time.c_str(), NK_TEXT_LEFT, nk_rgb(255, 0, 0));
        }

        nk_end(nuklear_context_.get());
        //        DrawText(fps.c_str(), debug_fps_position_x, debug_fps_position_y, debug_fps_font_size, RED);
        //
        //        constexpr auto debug_frame_time_position_x = 150;
        //        constexpr auto debug_frame_time_position_y = 0;
        //        constexpr auto debug_frame_time_font_size  = 20;
        //        DrawText(frame_time.c_str(), debug_frame_time_position_x, debug_frame_time_position_y,
        //                 debug_frame_time_font_size, RED);
    }
    catch (const std::exception &e)
    {
        spdlog::error("{}", e.what());
    }
}

void missileengine::Game::run() noexcept
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
        while (accumulator >= std::chrono::duration<float>(missileengine::UPDATE_RATE))
        {
            // FixedTick
            this->fixed_update(missileengine::UPDATE_RATE);
            accumulator -= std::chrono::duration<float>(missileengine::UPDATE_RATE);
        }

        // Tick
        auto delta_time = std::chrono::duration<float>(frame_time).count();
        this->update(delta_time);

        // Render
        this->render();

        scene_manager_->on_post_update();
    }
}
void missileengine::Game::close() noexcept
{
    spdlog::trace("Game::close() called.");
    window_.Close();
    spdlog::trace("Game::close() finished.");
}

missileengine::Game &missileengine::Game::get_instance() noexcept
{
    assert(INSTANCE != nullptr);
    return *INSTANCE;
}

missileengine::AssetManager &missileengine::Game::asset_manager() noexcept
{
    return *asset_manager_;
}

missileengine::SceneManager &missileengine::Game::scene_manager() noexcept
{
    return *scene_manager_;
}

missileengine::InputManager &missileengine::Game::input_manager() noexcept
{
    return *input_manager_;
}

missileengine::Scene &missileengine::Game::active_scene() noexcept
{
    return *scene_manager_->active_scene();
}
