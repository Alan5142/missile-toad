
#include "missile_toad/core/systems/renderer.system.hpp"
#include "missile_toad/core/components/box_collider_2d.component.hpp"
#include "missile_toad/core/components/camera_2d.component.hpp"
#include "missile_toad/core/components/rigidbody_2d.component.hpp"
#include "missile_toad/core/components/sprite.component.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include "missile_toad/core/game.hpp"

#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr auto PIXELS_PER_UNIT = 64.0F;

void missiletoad::core::RendererSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<core::RendererSystem>(ctx)
        .type("core::RendererSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<missiletoad::core::Game *>();
}

missiletoad::core::RendererSystem::RendererSystem(missiletoad::core::Game *game)
    : registry_(&game->active_scene().get_registry())
{
}

void missiletoad::core::RendererSystem::on_render()
{
    // Sort sprites by z-index
    registry_->sort<core::SpriteComponent>([](auto &lhs, auto &rhs) { return lhs.z_index < rhs.z_index; });
    registry_->sort<core::TransformComponent, core::SpriteComponent>();

    // Render sprites
    auto view = registry_->view<core::TransformComponent, core::SpriteComponent>();

    // Camera iterator
    auto camera_view = registry_->view<core::Camera2dComponent, core::TransformComponent>();

    for (auto cam_entity : camera_view)
    {
        auto &cam           = registry_->get<core::Camera2dComponent>(cam_entity);
        auto &cam_transform = registry_->get<core::TransformComponent>(cam_entity);

        cam.set_target({cam_transform.position.x, cam_transform.position.y});
        cam.set_rotation(cam_transform.rotation);

        BeginMode2D(cam.get_camera());
        for (auto entity : registry_->view<core::SpriteComponent>())
        {
            auto &transform  = view.get<core::TransformComponent>(entity);
            auto &sprite     = view.get<core::SpriteComponent>(entity);
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

            auto rectangle_dest = Rectangle{.x      = PIXELS_PER_UNIT * transform.position.x,
                                            .y      = PIXELS_PER_UNIT * transform.position.y,
                                            .width  = PIXELS_PER_UNIT * transform.scale.x,
                                            .height = PIXELS_PER_UNIT * transform.scale.y};

            auto color = raylib::Color(sprite.color.r, sprite.color.g, sprite.color.b, sprite.color.a);

            DrawTexturePro(sprite_tex,
                           rectangle_src,                                                      //
                           rectangle_dest,                                                     //
                           Vector2{rectangle_dest.width / 2.0F, rectangle_dest.height / 2.0F}, //
                           transform.rotation, color);
        }
        EndMode2D();
    }

    // Draw Physics Objects
    for (auto cam_entity : camera_view)
    {
        auto &cam = registry_->get<core::Camera2dComponent>(cam_entity);
        BeginMode2D(cam.get_camera());
        for (auto entity : registry_->view<core::BoxCollider2dComponent, core::TransformComponent>())
        {
            const auto &box_collider = registry_->get<missiletoad::core::BoxCollider2dComponent>(entity);
            const auto &transform    = view.get<core::TransformComponent>(entity);
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
