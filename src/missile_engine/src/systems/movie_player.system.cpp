
#include "missile_engine/systems/movie_player.system.hpp"
#include "missile_engine/components/disabled.component.hpp"
#include "missile_engine/components/movie_player.component.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

missileengine::MoviePlayerSystem::MoviePlayerSystem(missileengine::Game *game)
{
    unused(game);
}

void missileengine::MoviePlayerSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::MoviePlayerSystem>(ctx)
        .type("missileengine::MoviePlayerSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
}

void missileengine::MoviePlayerSystem::on_update(float delta_time)
{

    auto &scene = Game::get_instance().active_scene();

    auto view = scene.view<missileengine::MoviePlayerComponent>(entt::exclude<missileengine::DisabledComponent>);

    for (auto entity : view)
    {
        auto &movie_player_component = view.get<missileengine::MoviePlayerComponent>(entity);

        // Call update on the movie.
        if (movie_player_component.movie)
        {
            movie_player_component.movie->update(delta_time);
            movie_player_component.movie->texture_.Update(movie_player_component.movie->image_.GetData());
        }
    }
}
