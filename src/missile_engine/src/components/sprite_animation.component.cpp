
#include "missile_engine/components/sprite_animation.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::SpriteAnimationComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::SpriteAnimationComponent>(ctx)
        .type("missileengine::SpriteAnimationComponent"_hs)
        .data<&missileengine::SpriteAnimationComponent::is_playing>("is_playing"_hs)
        .data<&missileengine::SpriteAnimationComponent::loop>("loop"_hs)
        .data<nullptr, &missileengine::SpriteAnimationComponent::get_current_frame_texture>("current_frame_texture"_hs)
        .data<&missileengine::SpriteAnimationComponent::set_frame, &missileengine::SpriteAnimationComponent::get_frame>(
            "frame"_hs)
        .data<nullptr, &missileengine::SpriteAnimationComponent::get_frame_count>("frame_count"_hs)
        .func<&missileengine::SpriteAnimationComponent::add_frame>("add_frame"_hs)
        .func<&missileengine::SpriteAnimationComponent::remove_frame>("remove_frame"_hs);
}

void missileengine::SpriteAnimationComponent::update(std::chrono::duration<float> delta_time) noexcept
{
    if (!is_playing)
    {
        return;
    }
    frame_timer_.tick(delta_time);
    if (frame_timer_.finished())
    {
        current_frame_ = (current_frame_ + 1) % frames_.size();
        if (loop)
        {
            frame_timer_.reset();
        }
        else
        {
            is_playing = false;
        }
    }
}

void missileengine::SpriteAnimationComponent::set_timer(missileengine::Timer timer)
{
    frame_timer_ = timer;
}

void missileengine::SpriteAnimationComponent::add_frame(entt::resource<Texture> frame)
{
    frames_.push_back(frame);
}

void missileengine::SpriteAnimationComponent::remove_frame(uint32_t frame)
{
    frames_.erase(frames_.begin() + frame);
}

void missileengine::SpriteAnimationComponent::set_frame(uint32_t frame)
{
    current_frame_ = frame % frames_.size();
}

uint32_t missileengine::SpriteAnimationComponent::get_frame() const
{
    return current_frame_;
}

uint32_t missileengine::SpriteAnimationComponent::get_frame_count() const
{
    return static_cast<uint32_t>(frames_.size());
}

entt::resource<missileengine::Texture> missileengine::SpriteAnimationComponent::get_current_frame_texture()
{
    return frames_[current_frame_];
}
