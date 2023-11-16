
#include "missile_engine/systems/renderer.system.hpp"

#include "box2d/b2_circle_shape.h"
#include "missile_engine/components/box_collider_2d.component.hpp"
#include "missile_engine/components/camera_2d.component.hpp"
#include "missile_engine/components/circle_collider_2d.component.hpp"
#include "missile_engine/components/disabled.component.hpp"
#include "missile_engine/components/line_renderer.component.hpp"
#include "missile_engine/components/movie_player.component.hpp"
#include "missile_engine/components/sprite.component.hpp"
#include "missile_engine/components/transform.component.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr auto CENTER_RATIO = 2.0F;

void missileengine::RendererSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<RendererSystem>(ctx)
        .type("RendererSystem"_hs)
        .base<missileengine::BaseSystem>()
        .ctor<missileengine::Game *>();
}

missileengine::RendererSystem::RendererSystem(missileengine::Game *game)
    : registry_(&game->active_scene().get_registry())
{
}

void missileengine::RendererSystem::on_render()
{
    // Sort sprites by z-index
    registry_->sort<SpriteComponent>([](auto &lhs, auto &rhs) { return lhs.z_index < rhs.z_index; });
    registry_->sort<TransformComponent, SpriteComponent>();

    // Camera iterator
    auto camera_view = registry_->view<Camera2dComponent, TransformComponent>(entt::exclude<DisabledComponent>);

    const auto has_debug_mode = Game::get_instance().debug_mode();

    for (auto cam_entity : camera_view)
    {
        auto &cam           = registry_->get<Camera2dComponent>(cam_entity);
        auto &cam_transform = registry_->get<TransformComponent>(cam_entity);

        cam.set_target({cam_transform.position.x * PIXELS_PER_UNIT, cam_transform.position.y * PIXELS_PER_UNIT});
        cam.set_rotation(cam_transform.rotation);

        BeginTextureMode(cam.get_render_texture());
        ClearBackground(BLACK);
        BeginMode2D(cam.get_camera());
        for (auto entity : registry_->view<TransformComponent, SpriteComponent>(entt::exclude<DisabledComponent>))
        {
            draw_sprite(entity);
        }

        for (const auto entity : registry_->view<LineRendererComponent>())
        {
            draw_line(entity);
        }

        for (const auto entity :
             registry_->view<MoviePlayerComponent, TransformComponent>(entt::exclude<DisabledComponent>))
        {
            draw_movie(entity);
        }

        if (has_debug_mode)
        {

            for (const auto entity :
                 registry_->view<BoxCollider2dComponent, TransformComponent>(entt::exclude<DisabledComponent>))
            {
                debug_draw_physics(entity);
            }

            for (const auto entity :
                 registry_->view<CircleCollider2dComponent, TransformComponent>(entt::exclude<DisabledComponent>))
            {
                debug_draw_circle_physics(entity);
            }
        }
    }
    EndMode2D();
    EndTextureMode();
}

void missileengine::RendererSystem::draw_sprite(const entt::entity entity)
{
    auto &transform  = registry_->get<TransformComponent>(entity);
    auto &sprite     = registry_->get<SpriteComponent>(entity);
    auto &sprite_tex = sprite.texture->get_texture();

    auto rectangle_src = Rectangle{
        .x = 0, .y = 0, .width = static_cast<float>(sprite_tex.width), .height = static_cast<float>(sprite_tex.height)};

    if (sprite.scissors.has_value())
    {
        const auto scissors  = sprite.scissors.value();
        rectangle_src.x      = scissors.x;
        rectangle_src.y      = scissors.y;
        rectangle_src.width  = scissors.z;
        rectangle_src.height = scissors.w;
    }

    const auto scale_x = (rectangle_src.width / PIXELS_PER_UNIT) * transform.scale.x;
    const auto scale_y = (rectangle_src.height / PIXELS_PER_UNIT) * transform.scale.y;

    auto rectangle_dest = Rectangle{.x      = PIXELS_PER_UNIT * transform.position.x,
                                    .y      = PIXELS_PER_UNIT * transform.position.y,
                                    .width  = PIXELS_PER_UNIT * scale_x,
                                    .height = PIXELS_PER_UNIT * scale_y};

    auto color = Color{
        .r = sprite.color.r,
        .g = sprite.color.g,
        .b = sprite.color.b,
        .a = sprite.color.a,
    };

    DrawTexturePro(sprite_tex,
                   rectangle_src,                                                                      //
                   rectangle_dest,                                                                     //
                   Vector2{rectangle_dest.width / CENTER_RATIO, rectangle_dest.height / CENTER_RATIO}, //
                   transform.rotation, color);
}

void missileengine::RendererSystem::draw_line(const entt::entity entity)
{
    const auto &line  = registry_->get<LineRendererComponent>(entity);
    const auto  color = Color{
         .r = line.color.r,
         .g = line.color.g,
         .b = line.color.b,
         .a = line.color.a,
    };
    DrawLineEx(Vector2{PIXELS_PER_UNIT * line.start.x, PIXELS_PER_UNIT * line.start.y},
               Vector2{PIXELS_PER_UNIT * line.end.x, PIXELS_PER_UNIT * line.end.y}, line.width, color);
}

void missileengine::RendererSystem::debug_draw_physics(const entt::entity entity)
{
    const auto &box_collider = registry_->get<missileengine::BoxCollider2dComponent>(entity);
    const auto &transform    = registry_->get<missileengine::TransformComponent>(entity);
    const auto &position     = transform.position;

    auto *polygon      = dynamic_cast<b2PolygonShape *>(box_collider.get_fixture()->GetShape());
    auto  vertex_count = polygon->m_count;
    auto  vertices     = std::span(polygon->m_vertices);
    // Consider rotating the vertices by the transform.rotation
    for (auto i = 0; i < vertex_count; i++)
    {
        auto vertex      = vertices[i];
        auto next_vertex = vertices[(i + 1) % vertex_count];
        // Rotate the vertices by the transform.rotation
        auto rotation_matrix     = glm::rotate(glm::mat4(1.0F), glm::radians(transform.rotation), glm::vec3(0, 0, 1));
        auto rotated_vertex      = rotation_matrix * glm::vec4(vertex.x, vertex.y, 0, 1);
        auto rotated_next_vertex = rotation_matrix * glm::vec4(next_vertex.x, next_vertex.y, 0, 1);

        auto x = PIXELS_PER_UNIT * (position.x + rotated_vertex.x);
        auto y = PIXELS_PER_UNIT * (position.y + rotated_vertex.y);
        auto w = PIXELS_PER_UNIT * (position.x + rotated_next_vertex.x);
        auto h = PIXELS_PER_UNIT * (position.y + rotated_next_vertex.y);

        DrawLineEx(Vector2{x, y}, Vector2{w, h}, 1.0F, GREEN);
    }
}

void missileengine::RendererSystem::debug_draw_circle_physics(entt::entity entity)
{
    const auto &box_collider = registry_->get<missileengine::CircleCollider2dComponent>(entity);
    const auto &transform    = registry_->get<missileengine::TransformComponent>(entity);
    const auto &position     = transform.position;

    auto *circle = dynamic_cast<b2CircleShape *>(box_collider.get_fixture()->GetShape());

    const auto x = static_cast<int>(PIXELS_PER_UNIT * position.x);
    const auto y = static_cast<int>(PIXELS_PER_UNIT * position.y);
    DrawCircleLines(x, y, circle->m_radius * PIXELS_PER_UNIT, GREEN);
}

void missileengine::RendererSystem::draw_movie(const entt::entity entity)
{
    auto &movie_player_component = registry_->get<MoviePlayerComponent>(entity);
    auto &transform              = registry_->get<TransformComponent>(entity);

    if (movie_player_component.movie)
    {
        const auto movie_size = movie_player_component.movie->get_size();
        DrawTexturePro(
            movie_player_component.movie->get_texture(),
            Rectangle{
                .x = 0, .y = 0, .width = static_cast<float>(movie_size.x), .height = static_cast<float>(movie_size.y)},
            Rectangle{.x      = PIXELS_PER_UNIT * transform.position.x,
                      .y      = PIXELS_PER_UNIT * transform.position.y,
                      .width  = PIXELS_PER_UNIT * transform.scale.x,
                      .height = PIXELS_PER_UNIT * transform.scale.y},
            {transform.scale.x * PIXELS_PER_UNIT, transform.scale.y * PIXELS_PER_UNIT}, transform.rotation, WHITE);
    }
}
