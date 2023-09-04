#include "missile_toad/game.hpp"
#include "nuklear.h"
#include "raylib-nuklear.h"
#include "fmt/format.h"

missiletoad::Game::Game(int argc, char **argv) noexcept : argc(argc), argv(argv), nuklear_context(nullptr, nullptr)
{
    nuklear_context = std::unique_ptr<nk_context, void (*)(nk_context *)>(InitNuklear(16), UnloadNuklear);
}

// TODO: Implement this.
missiletoad::Game::~Game() noexcept = default;

void missiletoad::Game::update(float /*delta_time*/) noexcept
{
    (void)this->argc;
    (void)this->argv;

    // The first step is to update the nuklear context so that it can handle input.
    UpdateNuklear(nuklear_context.get());

    if (nk_begin(nuklear_context.get(), "Demo", nk_rect(50, 50, 200, 200), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        nk_layout_row_dynamic(nuklear_context.get(), 30, 1);
        if (nk_button_label(nuklear_context.get(), "button") == 1)
        {
            fmt::print("button pressed!\n");
        }
    }
    nk_end(nuklear_context.get());
}

void missiletoad::Game::fixed_update(float /*delta_time*/) noexcept
{

}

void missiletoad::Game::render() noexcept
{
    // TODO: Implement this.
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        DrawNuklear(nuklear_context.get());
    }
    EndDrawing();


}
