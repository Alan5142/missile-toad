
#include "missile_engine/components/sprite_animation.component.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>

void missileengine::SpriteAnimationComponent::register_component(entt::meta_ctx &ctx)
{
    using namespace entt::literals;
    entt::meta<missileengine::SpriteAnimationState>(ctx)
        .type("missileengine::SpriteAnimationState"_hs)
        .data<nullptr, &missileengine::SpriteAnimationState::get_current_frame_texture>("current_frame_texture"_hs)
        .data<&missileengine::SpriteAnimationState::set_frame, &missileengine::SpriteAnimationState::get_frame>(
            "frame"_hs)
        .data<nullptr, &missileengine::SpriteAnimationState::get_frame_count>("frame_count"_hs)
        .func<&missileengine::SpriteAnimationState::add_frame>("add_frame"_hs)
        .func<&missileengine::SpriteAnimationState::remove_frame>("remove_frame"_hs);

    entt::meta<missileengine::SpriteAnimationComponent>(ctx)
        .type("missileengine::SpriteAnimationComponent"_hs)
        .data<&missileengine::SpriteAnimationComponent::states_>("states"_hs)
        .data<&missileengine::SpriteAnimationComponent::current_state_>("current_state"_hs);
}

void missileengine::SpriteAnimationComponent::add_state(std::string_view                    state_to,
                                                        missileengine::SpriteAnimationState state)
{
    states_.emplace(std::hash<std::string_view>{}(state_to), state);
}

void missileengine::SpriteAnimationComponent::remove_state(std::string_view name)
{
    states_.erase(std::hash<std::string_view>{}(name));
}

void missileengine::SpriteAnimationComponent::transition_to(std::string_view name)
{
    const auto current_state = states_.find(current_state_);
    if (current_state == states_.end())
    {
        return;
    }
    current_state->second.get_transition(name).should_transition(true);
}

void missileengine::SpriteAnimationComponent::force_transition_to(std::string_view name)
{
    current_state_ = std::hash<std::string_view>{}(name);
}

missileengine::SpriteAnimationTransition::SpriteAnimationTransition(bool should_transition)
    : should_transition_(should_transition)
{
}

void missileengine::SpriteAnimationComponent::update(std::chrono::duration<float> delta_time) noexcept
{
    auto current_state = states_.find(current_state_);
    if (current_state == states_.end())
    {
        return;
    }
    if (auto transition = current_state->second.update(delta_time); transition)
    {
        current_state_ = *transition;
    }
}

std::optional<std::size_t> missileengine::SpriteAnimationState::update(std::chrono::duration<float> delta_time) noexcept
{
    auto check_for_transition = [this]() mutable -> std::optional<std::size_t>
    {
        for (const auto &[id, transition] : transitions_)
        {
            if (transition.should_transition())
            {
                return id;
            }
        }
        return std::nullopt;
    };
    if (!is_playing_)
    {
        return std::nullopt;
    }
    frame_timer_.tick(delta_time);
    if (frame_timer_.finished())
    {
        current_frame_ = (current_frame_ + 1) % frames_.size();
        if (current_frame_ == 0)
        {
            // Check if there is a transition.
            if (auto transition = check_for_transition(); transition)
            {
                return transition;
            }
            if (loop_)
            {
                frame_timer_.reset();
            }
            else
            {
                is_playing_ = false;
            }
        }
        else if (wait_for_finish_)
        {
            // Check if there is a transition.
            if (auto transition = check_for_transition(); transition)
            {
                return transition;
            }
        }
    }

    return std::nullopt;
}

void missileengine::SpriteAnimationState::set_timer(missileengine::Timer timer)
{
    frame_timer_ = timer;
    frame_timer_.set_loop(true);
}

void missileengine::SpriteAnimationState::add_frame(entt::resource<Texture> frame)
{
    frames_.push_back(frame);
}

void missileengine::SpriteAnimationState::remove_frame(uint32_t frame)
{
    frames_.erase(frames_.begin() + frame);
}

void missileengine::SpriteAnimationState::set_frame(uint32_t frame)
{
    current_frame_ = frame % frames_.size();
}

uint32_t missileengine::SpriteAnimationState::get_frame() const
{
    return current_frame_;
}

uint32_t missileengine::SpriteAnimationState::get_frame_count() const
{
    return static_cast<uint32_t>(frames_.size());
}

entt::resource<missileengine::Texture> missileengine::SpriteAnimationState::get_current_frame_texture()
{
    return frames_[current_frame_];
}

void missileengine::SpriteAnimationState::add_transition(std::string_view                         state_to,
                                                         missileengine::SpriteAnimationTransition transition)
{
    this->transitions_.emplace(std::hash<std::string_view>{}(state_to), transition);
}

void missileengine::SpriteAnimationState::remove_transition(std::string_view next)
{
    transitions_.erase(std::hash<std::string_view>{}(next));
}

missileengine::SpriteAnimationState::SpriteAnimationState(std::string_view name) noexcept
    : name_hash_(std::hash<std::string_view>{}(name))
{
}

missileengine::SpriteAnimationState::SpriteAnimationState(std::size_t name_hash) noexcept : name_hash_(name_hash)
{
}

bool missileengine::SpriteAnimationTransition::should_transition() const
{
    return should_transition_;
}

void missileengine::SpriteAnimationTransition::should_transition(bool should_transition)
{
    should_transition_ = should_transition;
}
