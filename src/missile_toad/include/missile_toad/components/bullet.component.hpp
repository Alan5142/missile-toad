#pragma once
#include "missile_engine/common.hpp"

#include <entt/meta/meta.hpp>
#include <glm/vec2.hpp>

namespace missiletoad
{
    class BulletComponent
    {
    public:
        float     velocity  = 1.0f;
        glm::vec2 direction = {};

        static void register_component(entt::meta_ctx &ctx);
    };
} // namespace missiletoad

// - Crear una lista de X cantidad de bullets que tengan la propiedad active/deactivated (pool)
// - Hacer el disparo el cual consiste en un activar una bullet y dirigirla a la boca del cañon. Y de ahi hacer que se
// mueva en una velocidad constante hacia la pendiente definida al momento del disparo.
// - Detectar las colisiones y dejarlas preparadas para que puedan afectar de diferente manera (pared, enemigo)
