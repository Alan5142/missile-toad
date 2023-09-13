
#include "missile_toad/core/systems/renderer.system.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "missile_toad/core/components/camera_2d.component.hpp"
#include "missile_toad/core/components/physics_2d.component.hpp"
#include "missile_toad/core/components/sprite.component.hpp"
#include "missile_toad/core/components/transform.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <glm/glm.hpp>
#include <rlgl.h>

constexpr auto PIXELS_PER_UNIT = 3.0F;

missiletoad::core::RendererSystem::RendererSystem() : registry_(*entt::locator<entt::registry *>::value())
{
}

void missiletoad::core::RendererSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<core::RendererSystem>(ctx)
        .type("core::RendererSystem"_hs)
        .base<missiletoad::core::BaseSystem>()
        .ctor<>();
}

void missiletoad::core::RendererSystem::on_render()
{
    // Sort sprites by z-index
    registry_.sort<core::SpriteComponent>([](auto &lhs, auto &rhs) { return lhs.z_index < rhs.z_index; });
    registry_.sort<core::TransformComponent, core::SpriteComponent>();

    // Render sprites
    auto view = registry_.view<core::TransformComponent, core::SpriteComponent>();

    // Camera iterator
    auto camera_view = registry_.view<core::Camera2dComponent, core::TransformComponent>();

    for (auto cam_entity : camera_view)
    {
        auto &cam           = registry_.get<core::Camera2dComponent>(cam_entity);
        auto &cam_transform = registry_.get<core::TransformComponent>(cam_entity);

        cam.camera.target   = Vector2{cam_transform.position.x, cam_transform.position.y};
        cam.camera.rotation = cam_transform.rotation;

        BeginMode2D(cam.camera);
        for (auto entity : registry_.view<core::SpriteComponent>())
        {
            auto &transform  = view.get<core::TransformComponent>(entity);
            auto &sprite     = view.get<core::SpriteComponent>(entity);
            auto &sprite_tex = sprite.texture->get_texture();

            auto rectangle_src = Rectangle{.x      = 0,
                                           .y      = 0,
                                           .width  = static_cast<float>(sprite_tex.width),
                                           .height = static_cast<float>(sprite_tex.height)};

            auto rectangle_dest = Rectangle{.x      = transform.position.x,
                                            .y      = transform.position.y,
                                            .width  = PIXELS_PER_UNIT * transform.scale.x,
                                            .height = PIXELS_PER_UNIT * transform.scale.y};

            DrawTexturePro(sprite_tex, rectangle_src, rectangle_dest, {1.0F, 1.0F}, transform.rotation, WHITE);
        }
        EndMode2D();
    }

    // Draw Physics Objects
    for (auto cam_entity : camera_view)
    {
        auto &cam = registry_.get<core::Camera2dComponent>(cam_entity);
        BeginMode2D(cam.camera);
        for (auto entity : registry_.view<core::Physics2dComponent>())
        {
            auto &physics = registry_.get<missiletoad::core::Physics2dComponent>(entity);
            //        auto &transform = registry.get<missiletoad::core::TransformComponent>(entity);
            auto *body     = physics.get_body();
            auto  position = body->GetPosition();
            //        auto  angle    = body->GetAngle();
            auto shape = body->GetFixtureList()->GetShape();
            auto type  = shape->GetType();
            if (type == b2Shape::e_polygon)
            {
                auto *polygon      = static_cast<b2PolygonShape *>(shape);
                auto  vertex_count = polygon->m_count;
                auto *vertices     = polygon->m_vertices;
                for (auto i = 0; i < vertex_count; i++)
                {
                    auto vertex      = vertices[i];
                    auto next_vertex = vertices[(i + 1) % vertex_count];
                    DrawLineEx({position.x + vertex.x + 0.5F, position.y + vertex.y + 0.5F},
                               {position.x + next_vertex.x + 0.5F, position.y + next_vertex.y + 0.5F}, 0.1F, GREEN);
                }
            }
        }
        EndMode2D();
    }
}
