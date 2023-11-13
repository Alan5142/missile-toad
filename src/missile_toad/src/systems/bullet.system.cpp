
#include "missile_toad/systems/bullet.system.hpp"
#include "missile_engine/game.hpp"
#include "missile_engine/asset_manager.hpp"

#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>

missiletoad::BulletSystem::BulletSystem(missileengine::Game *game)
{
    unused(game);
}

void missiletoad::BulletSystem::register_system(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::BulletSystem>(ctx)
            .type("missiletoad::BulletSystem"_hs)
            .base<missileengine::BaseSystem>()
            .ctor<missileengine::Game*>();
    // TODO: Add your register code here
}

void missiletoad::BulletSystem::on_start(){
    spdlog::trace("missiletoad::BulletSystem::on_start() called.");
    // auto &game         = missileengine::Game::get_instance();
    // auto &scene        = game.active_scene();

    // auto bullet_texture = game.asset_manager().load<missileengine::Texture>("/assets/sprites/bullets/bala.png");
    // const auto bullet_transform_scale = glm::vec2{0.2F, 0.2F};


    
}


void missiletoad::BulletSystem::on_update(float delta_time){
    unused(delta_time);
}

