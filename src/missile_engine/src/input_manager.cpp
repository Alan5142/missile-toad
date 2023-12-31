#include "missile_engine/input_manager.hpp"
#include <glm/vec2.hpp>

void missileengine::InputManager::update()
{
    process_actions();
    process_axis();
}

void missileengine::InputManager::add_action(std::string_view name, missileengine::Action action)
{
    auto action_it = actions_.find(name.data());
    if (action_it == actions_.end())
    {
        action_it               = actions_.emplace(name.data(), ActionData{}).first;
        action_it->second.state = EActionState::RELEASED;
    }
    action_it->second.actions.emplace_back(action);
}

missileengine::EActionState process_single_action(const missileengine::InputManager &self,
                                                  const missileengine::Action       &action)
{
    if (std::holds_alternative<missileengine::EKey>(action))
    {
        return self.is_key_pressed(std::get<missileengine::EKey>(action)) ? missileengine::EActionState::PRESSED
                                                                          : missileengine::EActionState::RELEASED;
    }
    if (std::holds_alternative<missileengine::EMouseButton>(action))
    {
        return self.is_mouse_button_pressed(std::get<missileengine::EMouseButton>(action))
                   ? missileengine::EActionState::PRESSED
                   : missileengine::EActionState::RELEASED;
    }
    if (std::holds_alternative<missileengine::GamepadButtonData>(action))
    {
        auto gamepad_button = std::get<missileengine::GamepadButtonData>(action);
        return self.is_gamepad_button_pressed(gamepad_button.gamepad, gamepad_button.button)
                   ? missileengine::EActionState::PRESSED
                   : missileengine::EActionState::RELEASED;
    }
    return missileengine::EActionState::RELEASED;
}

void missileengine::InputManager::process_actions()
{
    for (auto &[name, action_data] : actions_)
    {
        EActionState new_state = EActionState::RELEASED;
        for (const auto &action : action_data.actions)
        {
            EActionState action_state = process_single_action(*this, action);
            if (action_state == EActionState::PRESSED)
            {
                new_state = EActionState::PRESSED;
                break;
            }
        }

        switch (action_data.state)
        {
        case EActionState::RELEASED:
            if (new_state == EActionState::PRESSED)
            {
                action_data.state = EActionState::PRESSED;
            }
            break;
        case EActionState::PRESSED:
            if (new_state == EActionState::RELEASED)
            {
                action_data.state = EActionState::RELEASED;
            }
            else
            {
                action_data.state = EActionState::DOWN;
            }
            break;
        case EActionState::DOWN:
            if (new_state == EActionState::RELEASED)
            {
                action_data.state = EActionState::RELEASED;
            }
            break;
        case EActionState::UP:
            if (new_state == EActionState::PRESSED)
            {
                action_data.state = EActionState::PRESSED;
            }
            break;
        }
    }
}

float process_axis_button(missileengine::InputManager &self, const missileengine::AxisButton::AxisType &axis)
{
    namespace mt = missileengine;

    if (std::holds_alternative<mt::EKey>(axis))
    {
        const auto pressed = self.is_key_down(std::get<mt::EKey>(axis));
        return pressed ? 1.0F : 0.0F;
    }
    if (std::holds_alternative<mt::EMouseButton>(axis))
    {
        return self.is_mouse_button_down(std::get<mt::EMouseButton>(axis)) ? 1.0F : 0.0F;
    }
    if (std::holds_alternative<mt::GamepadButtonData>(axis))
    {
        auto gamepad_button = std::get<mt::GamepadButtonData>(axis);
        return self.is_gamepad_button_down(gamepad_button.gamepad, gamepad_button.button) ? 1.0F : 0.0F;
    }
    return 0.0F;
}

float process_single_axis(missileengine::InputManager &self, const missileengine::Axis::AxisType &axis)
{
    namespace mt = missileengine;

    if (std::holds_alternative<mt::AxisButton>(axis))
    {
        const auto &axis_button = std::get<mt::AxisButton>(axis);
        return process_axis_button(self, axis_button.positive) - process_axis_button(self, axis_button.negative);
    }
    if (std::holds_alternative<mt::GamepadAxisData>(axis))
    {
        auto gamepad_axis = std::get<mt::GamepadAxisData>(axis);
        return self.get_gamepad_axis(gamepad_axis.gamepad, gamepad_axis.axis);
    }
    return 0.0F;
}

void missileengine::InputManager::process_axis()
{
    for (auto &[name, axis_data] : axes_)
    {
        float value = 0.0F;
        for (const auto &axis : axis_data.axes)
        {
            float current_value = process_single_axis(*this, axis.axis);

            // Use deadzone, values between 0.0F and deadzone are clamped to 0.0F
            if (current_value <= axis.dead_zone && current_value >= -axis.dead_zone)
            {
                current_value = 0.0F;
            }
            else if (current_value > 0.0F)
            {
                current_value = (current_value - axis.dead_zone) / (1.0F - axis.dead_zone);
            }
            else
            {
                current_value = (current_value + axis.dead_zone) / (1.0F - axis.dead_zone);
            }

            // Apply weight
            value += current_value * axis.weight;
        }

        // Use deadzone
        switch (compare_float(value, 0.0F))
        {
        case EFloatCompare::LESS_THAN:
            value = -1.0F;
            break;
        case EFloatCompare::EQUAL:
            value = 0.0F;
            break;
        case EFloatCompare::GREATER_THAN:
            value = 1.0F;
            break;
        }

        axis_data.value = value;
    }
}
void missileengine::InputManager::clear_action(std::string_view name)
{
    actions_.erase(name.data());
}
missileengine::EActionState missileengine::InputManager::get_action(std::string_view name) const
{
    auto action_it = actions_.find(name.data());
    if (action_it == actions_.end())
    {
        return EActionState::RELEASED;
    }
    return action_it->second.state;
}

void missileengine::InputManager::add_axis(std::string_view name, missileengine::Axis axis)
{
    auto axis_it = axes_.find(name.data());
    if (axis_it == axes_.end())
    {
        axis_it = axes_.emplace(name.data(), AxisData{}).first;
    }
    axis_it->second.axes.emplace_back(axis);
}

void missileengine::InputManager::clear_axis(std::string_view name)
{
    axes_.erase(name.data());
}

float missileengine::InputManager::get_axis(std::string_view name) const
{
    auto axis_it = axes_.find(name.data());
    if (axis_it == axes_.end())
    {
        return 0.0F;
    }
    return axis_it->second.value;
}

glm::vec2 missileengine::InputManager::get_mouse_position() const
{
    auto mouse_position = GetMousePosition();
    return {mouse_position.x, mouse_position.y};
}
