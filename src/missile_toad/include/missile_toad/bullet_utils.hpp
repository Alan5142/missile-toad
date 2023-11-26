#pragma once
#include <glm/glm.hpp>

namespace missiletoad
{
    void createBullet(glm::vec2 start_position, glm::vec2 objetive_position, float velocity, float damage);
} // namespace missiletoad
