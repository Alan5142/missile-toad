
#include "missile_toad/core/components/sprite_animation.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missiletoad::core::SpriteAnimationComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missiletoad::core::SpriteAnimationComponent>(ctx)
        .type("missiletoad::core::SpriteAnimationComponent"_hs)
        .data<&missiletoad::core::SpriteAnimationComponent::is_playing>("is_playing"_hs)
        .data<&missiletoad::core::SpriteAnimationComponent::loop>("loop"_hs)
        .data<nullptr, &missiletoad::core::SpriteAnimationComponent::get_current_frame_texture>(
            "current_frame_texture"_hs)
        .data<&missiletoad::core::SpriteAnimationComponent::set_frame,
              &missiletoad::core::SpriteAnimationComponent::get_frame>("frame"_hs)
        .data<nullptr, &missiletoad::core::SpriteAnimationComponent::get_frame_count>("frame_count"_hs)
        .func<&missiletoad::core::SpriteAnimationComponent::add_frame>("add_frame"_hs)
        .func<&missiletoad::core::SpriteAnimationComponent::remove_frame>("remove_frame"_hs);
}

void missiletoad::core::SpriteAnimationComponent::update(std::chrono::duration<float> delta_time) noexcept
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

void missiletoad::core::SpriteAnimationComponent::set_timer(missiletoad::core::Timer timer)
{
    frame_timer_ = timer;
}

void missiletoad::core::SpriteAnimationComponent::add_frame(entt::resource<Texture> frame)
{
    frames_.push_back(frame);
}

void missiletoad::core::SpriteAnimationComponent::remove_frame(uint32_t frame)
{
    frames_.erase(frames_.begin() + frame);
}

void missiletoad::core::SpriteAnimationComponent::set_frame(uint32_t frame)
{
    current_frame_ = frame % frames_.size();
}

uint32_t missiletoad::core::SpriteAnimationComponent::get_frame() const
{
    return current_frame_;
}

uint32_t missiletoad::core::SpriteAnimationComponent::get_frame_count() const
{
    return frames_.size();
}

entt::resource<missiletoad::core::Texture> missiletoad::core::SpriteAnimationComponent::get_current_frame_texture()
{
    return frames_[current_frame_];
}
