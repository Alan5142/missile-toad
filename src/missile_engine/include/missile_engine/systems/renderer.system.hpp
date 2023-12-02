#pragma once
#include "missile_engine/base_system.hpp"
#include "missile_engine/common.hpp"

#include <entt/entity/registry.hpp>
#include <entt/meta/meta.hpp>
#include <gsl/gsl>

namespace missileengine
{
    class Game;
    /**
     * @brief System that renders all entities with a `SpriteComponent` and `TransformComponent`.
     * @details It first sorts all entities by their `SpriteComponent`'s `z_index` value, then renders them.
     * Then, it uses entities with a `Camera2dComponent` to begin drawing.
     *
     * It also provides a debug rendering mode for physics bodies.
     */
    class RendererSystem : public missileengine::BaseSystem
    {
        entt::registry *registry_;

    public:
        /**
         * @brief Construct a new RendererSystem object.
         */
        RendererSystem(Game *game);

        RendererSystem(const RendererSystem &)            = delete;
        RendererSystem(RendererSystem &&)                 = delete;
        RendererSystem &operator=(const RendererSystem &) = delete;
        RendererSystem &operator=(RendererSystem &&)      = delete;

        ~RendererSystem() override = default;

        /**
         * Register this system with the meta context.
         * @param ctx The meta context to register with.
         */
        static void register_system(entt::meta_ctx &ctx);

        /**
         * Render all entities with a `SpriteComponent` and `TransformComponent`.
         *
         * Also renders debug physics bodies if `debug_physics` is true.
         */
        void on_render() override;

    private:
        /**
         * Draw a sprite.
         * @param entity The entity to draw.
         */
        void draw_sprite(entt::entity entity);

        /**
         * Draw a line.
         * @param entity The entity to draw.
         */
        void draw_line(entt::entity entity);

        /**
         * Draw a box collider (Debug)
         * @param entity The entity to draw.
         */
        void debug_draw_physics(entt::entity entity);

        /**
         *Draw a circle collider. (Debug)
         * @param entity The entity to draw.
         */
        void debug_draw_circle_physics(entt::entity entity);

        /**
         * Draws a movie.
         * @param entity The entity to draw.
         */
        void draw_movie(entt::entity entity);
    };
} // namespace missileengine
