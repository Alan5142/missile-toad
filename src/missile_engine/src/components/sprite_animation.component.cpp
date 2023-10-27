
#include "missile_engine/components/sprite_animation.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missilengine::SpriteAnimationComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missilengine::SpriteAnimationComponent>(ctx)
        .type("missilengine::SpriteAnimationComponent"_hs)
        .data<&missilengine::SpriteAnimationComponent::is_playing>("is_playing"_hs)
        .data<&missilengine::SpriteAnimationComponent::loop>("loop"_hs)
        .data<nullptr, &missilengine::SpriteAnimationComponent::get_current_frame_texture>("current_frame_texture"_hs)
        .data<&missilengine::SpriteAnimationComponent::set_frame, &missilengine::SpriteAnimationComponent::get_frame>(
            "frame"_hs)
        .data<nullptr, &missilengine::SpriteAnimationComponent::get_frame_count>("frame_count"_hs)
        .func<&missilengine::SpriteAnimationComponent::add_frame>("add_frame"_hs)
        .func<&missilengine::SpriteAnimationComponent::remove_frame>("remove_frame"_hs);
}

void missilengine::SpriteAnimationComponent::update(std::chrono::duration<float> delta_time) noexcept
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

void missilengine::SpriteAnimationComponent::set_timer(missilengine::Timer timer)
{
    frame_timer_ = timer;
}

void missilengine::SpriteAnimationComponent::add_frame(entt::resource<Texture> frame)
{
    frames_.push_back(frame);
}

void missilengine::SpriteAnimationComponent::remove_frame(uint32_t frame)
{
    frames_.erase(frames_.begin() + frame);
}

void missilengine::SpriteAnimationComponent::set_frame(uint32_t frame)
{
    current_frame_ = frame % frames_.size();
}

uint32_t missilengine::SpriteAnimationComponent::get_frame() const
{
    return current_frame_;
}

uint32_t missilengine::SpriteAnimationComponent::get_frame_count() const
{
    return static_cast<uint32_t>(frames_.size());
}

entt::resource<missilengine::Texture> missilengine::SpriteAnimationComponent::get_current_frame_texture()
{
    return frames_[current_frame_];
}
