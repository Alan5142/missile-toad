#include "missile_engine/physics_utils.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/scene.hpp"

#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

class RaycastCallback : public b2RayCastCallback
{
public:
    std::optional<missileengine::RaycastResult> raycast{};

    float ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float fraction) override
    {
        raycast = missileengine::RaycastResult{}; // reset

        raycast->point    = {point.x, point.y};
        raycast->normal   = {normal.x, normal.y};
        raycast->fraction = fraction;
        raycast->entity   = static_cast<entt::entity>(fixture->GetUserData().pointer);

        return fraction;
    }
};

std::optional<missileengine::RaycastResult> missileengine::Physics::raycast(glm::vec2 start, glm::vec2 end)
{
    auto &physics_world = missileengine::Game::get_instance().active_scene().physics_world_;

    RaycastCallback callback{};

    physics_world.RayCast(&callback, {start.x, start.y}, {end.x, end.y});

    return callback.raycast;
}

std::optional<missileengine::RaycastResult> missileengine::Physics::raycast(glm::vec2 start, glm::vec2 direction,
                                                                            float distance)
{
    const auto end_vector = start + (direction * distance);

    return raycast(start, end_vector);
}
