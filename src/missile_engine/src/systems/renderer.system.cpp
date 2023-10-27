
#include "missile_engine/systems/renderer.system.hpp"
#include "missile_engine/components/box_collider_2d.component.hpp"
#include "missile_engine/components/camera_2d.component.hpp"
#include "missile_engine/components/sprite.component.hpp"
#include "missile_engine/components/transform.component.hpp"
#include "missile_engine/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr auto CENTER_RATIO = 2.0F;

void missilengine::RendererSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<RendererSystem>(ctx)
        .type("RendererSystem"_hs)
        .base<missilengine::BaseSystem>()
        .ctor<missilengine::Game *>();
}

missilengine::RendererSystem::RendererSystem(missilengine::Game *game) : registry_(&game->active_scene().get_registry())
{
}

void missilengine::RendererSystem::on_render()
{
    // Sort sprites by z-index
    registry_->sort<SpriteComponent>([](auto &lhs, auto &rhs) { return lhs.z_index < rhs.z_index; });
    registry_->sort<TransformComponent, SpriteComponent>();

    // Render sprites
    auto view = registry_->view<TransformComponent, SpriteComponent>();

    // Camera iterator
    auto camera_view = registry_->view<Camera2dComponent, TransformComponent>();

    for (auto cam_entity : camera_view)
    {
        auto &cam           = registry_->get<Camera2dComponent>(cam_entity);
        auto &cam_transform = registry_->get<TransformComponent>(cam_entity);

        cam.set_target({cam_transform.position.x, cam_transform.position.y});
        cam.set_rotation(cam_transform.rotation);

        BeginMode2D(cam.get_camera());
        for (auto entity : registry_->view<SpriteComponent>())
        {
            auto &transform  = view.get<TransformComponent>(entity);
            auto &sprite     = view.get<SpriteComponent>(entity);
            auto &sprite_tex = sprite.texture->get_texture();

            auto rectangle_src = Rectangle{.x      = 0,
                                           .y      = 0,
                                           .width  = static_cast<float>(sprite_tex.width),
                                           .height = static_cast<float>(sprite_tex.height)};

            if (sprite.scissors.has_value())
            {
                auto scissors        = sprite.scissors.value();
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
        EndMode2D();
    }

    // Draw Physics Objects
    for (auto cam_entity : camera_view)
    {
        auto &cam = registry_->get<Camera2dComponent>(cam_entity);
        BeginMode2D(cam.get_camera());
        for (auto entity : registry_->view<BoxCollider2dComponent, TransformComponent>())
        {
            const auto &box_collider = registry_->get<missilengine::BoxCollider2dComponent>(entity);
            const auto &transform    = view.get<TransformComponent>(entity);
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
                auto rotation_matrix =
                    glm::rotate(glm::mat4(1.0F), glm::radians(transform.rotation), glm::vec3(0, 0, 1));
                auto rotated_vertex      = rotation_matrix * glm::vec4(vertex.x, vertex.y, 0, 1);
                auto rotated_next_vertex = rotation_matrix * glm::vec4(next_vertex.x, next_vertex.y, 0, 1);

                auto x = PIXELS_PER_UNIT * (position.x + rotated_vertex.x);
                auto y = PIXELS_PER_UNIT * (position.y + rotated_vertex.y);
                auto w = PIXELS_PER_UNIT * (position.x + rotated_next_vertex.x);
                auto h = PIXELS_PER_UNIT * (position.y + rotated_next_vertex.y);

                DrawLineEx(Vector2{x, y}, Vector2{w, h}, 1.0F, GREEN);
            }
        }
        EndMode2D();
    }
}
