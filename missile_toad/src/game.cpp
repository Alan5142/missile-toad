#include "missile_toad/game.hpp"
#include "fmt/format.h"
#include "nuklear.h"
#include "raylib-nuklear.h"
#include "missile_toad/base_system.hpp"

extern void register_system(entt::meta_ctx& ctx);

missiletoad::Game::Game(int argc, char **argv) noexcept : argc(argc), argv(argv), nuklear_context(nullptr, nullptr)
{
    nuklear_context = std::unique_ptr<nk_context, void (*)(nk_context *)>(InitNuklear(16), UnloadNuklear);

    // Register Systems meta types.
    register_system(this->meta_context);
    using namespace entt::literals;
    auto klass = entt::resolve("missiletoad::DummySystem"_hs);

    // Create a new instance of the DummySystem.
    auto instance = klass.construct();

    auto system = instance.try_cast<missiletoad::BaseSystem>();
    if (system)
    {
        fmt::print("Hello from DummyComponent!\n");
    }
}

// TODO: Implement this.
missiletoad::Game::~Game() noexcept = default;

void missiletoad::Game::update(float delta_time) noexcept
{
    unused(delta_time);
    unused(this->argc);
    unused(this->argv);

    // The first step is to update the nuklear context so that it can handle input.
    UpdateNuklear(nuklear_context.get());

    // TODO: Update the scene.
}

void missiletoad::Game::fixed_update(float /*delta_time*/) noexcept
{
    // TODO: Update the scene.
}

void missiletoad::Game::render() noexcept
{
    // TODO: Implement this.
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);

        // TODO: Update the scene.
        // this->current_scene->render();

        DrawNuklear(nuklear_context.get());
    }
    EndDrawing();
}
