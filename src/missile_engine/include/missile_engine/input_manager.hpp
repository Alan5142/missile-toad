#pragma once
#include "common.hpp"

#include <glm/vec2.hpp>
#include <raylib.h>
#include <unordered_map>
#include <variant>

namespace missileengine
{
    /**
     * @brief The keys on a keyboard.
     */
    enum class EKey
    {
        APOSTROPHE    = KEY_APOSTROPHE,
        COMMA         = KEY_COMMA,
        MINUS         = KEY_MINUS,
        PERIOD        = KEY_PERIOD,
        SLASH         = KEY_SLASH,
        ZERO          = KEY_ZERO,
        ONE           = KEY_ONE,
        TWO           = KEY_TWO,
        THREE         = KEY_THREE,
        FOUR          = KEY_FOUR,
        FIVE          = KEY_FIVE,
        SIX           = KEY_SIX,
        SEVEN         = KEY_SEVEN,
        EIGHT         = KEY_EIGHT,
        NINE          = KEY_NINE,
        SEMICOLON     = KEY_SEMICOLON,
        EQUAL         = KEY_EQUAL,
        A             = KEY_A,
        B             = KEY_B,
        C             = KEY_C,
        D             = KEY_D,
        E             = KEY_E,
        F             = KEY_F,
        G             = KEY_G,
        H             = KEY_H,
        I             = KEY_I,
        J             = KEY_J,
        K             = KEY_K,
        L             = KEY_L,
        M             = KEY_M,
        N             = KEY_N,
        O             = KEY_O,
        P             = KEY_P,
        Q             = KEY_Q,
        R             = KEY_R,
        S             = KEY_S,
        T             = KEY_T,
        U             = KEY_U,
        V             = KEY_V,
        W             = KEY_W,
        X             = KEY_X,
        Y             = KEY_Y,
        Z             = KEY_Z,
        LEFT_BRACKET  = KEY_LEFT_BRACKET,
        BACKSLASH     = KEY_BACKSLASH,
        RIGHT_BRACKET = KEY_RIGHT_BRACKET,
        GRAVE         = KEY_GRAVE,
        SPACE         = KEY_SPACE,
        ESCAPE        = KEY_ESCAPE,
        ENTER         = KEY_ENTER,
        TAB           = KEY_TAB,
        BACKSPACE     = KEY_BACKSPACE,
        INSERT        = KEY_INSERT,
        DELETE        = KEY_DELETE,
        RIGHT         = KEY_RIGHT,
        LEFT          = KEY_LEFT,
        DOWN          = KEY_DOWN,
        UP            = KEY_UP,
        PAGE_UP       = KEY_PAGE_UP,
        PAGE_DOWN     = KEY_PAGE_DOWN,
        HOME          = KEY_HOME,
        END           = KEY_END,
        CAPS_LOCK     = KEY_CAPS_LOCK,
        SCROLL_LOCK   = KEY_SCROLL_LOCK,
        NUM_LOCK      = KEY_NUM_LOCK,
        PRINT_SCREEN  = KEY_PRINT_SCREEN,
        PAUSE         = KEY_PAUSE,
        F1            = KEY_F1,
        F2            = KEY_F2,
        F3            = KEY_F3,
        F4            = KEY_F4,
        F5            = KEY_F5,
        F6            = KEY_F6,
        F7            = KEY_F7,
        F8            = KEY_F8,
        F9            = KEY_F9,
        F10           = KEY_F10,
        F11           = KEY_F11,
        F12           = KEY_F12,
        LEFT_SHIFT    = KEY_LEFT_SHIFT,
        LEFT_CONTROL  = KEY_LEFT_CONTROL,
        LEFT_ALT      = KEY_LEFT_ALT,
        LEFT_SUPER    = KEY_LEFT_SUPER,
        RIGHT_SHIFT   = KEY_RIGHT_SHIFT,
        RIGHT_CONTROL = KEY_RIGHT_CONTROL,
        RIGHT_ALT     = KEY_RIGHT_ALT,
        RIGHT_SUPER   = KEY_RIGHT_SUPER,
        KB_MENU       = KEY_KB_MENU,
        KP_0          = KEY_KP_0,
        KP_1          = KEY_KP_1,
        KP_2          = KEY_KP_2,
        KP_3          = KEY_KP_3,
        KP_4          = KEY_KP_4,
        KP_5          = KEY_KP_5,
        KP_6          = KEY_KP_6,
        KP_7          = KEY_KP_7,
        KP_8          = KEY_KP_8,
        KP_9          = KEY_KP_9,
        KP_DECIMAL    = KEY_KP_DECIMAL,
        KP_DIVIDE     = KEY_KP_DIVIDE,
        KP_MULTIPLY   = KEY_KP_MULTIPLY,
        KP_SUBTRACT   = KEY_KP_SUBTRACT,
        KP_ADD        = KEY_KP_ADD,
        KP_ENTER      = KEY_KP_ENTER,
        KP_EQUAL      = KEY_KP_EQUAL,
        BACK          = KEY_BACK,
        MENU          = KEY_MENU,
        VOLUME_UP     = KEY_VOLUME_UP,
        VOLUME_DOWN   = KEY_VOLUME_DOWN,
    };

    /**
     * @brief The mouse buttons.
     */
    enum class EMouseButton
    {
        LEFT    = MOUSE_BUTTON_LEFT,
        RIGHT   = MOUSE_BUTTON_RIGHT,
        MIDDLE  = MOUSE_BUTTON_MIDDLE,
        SIDE    = MOUSE_BUTTON_SIDE,
        EXTRA   = MOUSE_BUTTON_EXTRA,
        FORWARD = MOUSE_BUTTON_FORWARD,
        BACK    = MOUSE_BUTTON_BACK,
    };

    /**
     * @brief The gamepad buttons.
     */
    enum class EGamepadButton
    {
        UNKNOWN          = GAMEPAD_BUTTON_UNKNOWN,
        LEFT_FACE_UP     = GAMEPAD_BUTTON_LEFT_FACE_UP,
        LEFT_FACE_RIGHT  = GAMEPAD_BUTTON_LEFT_FACE_RIGHT,
        LEFT_FACE_DOWN   = GAMEPAD_BUTTON_LEFT_FACE_DOWN,
        LEFT_FACE_LEFT   = GAMEPAD_BUTTON_LEFT_FACE_LEFT,
        RIGHT_FACE_UP    = GAMEPAD_BUTTON_RIGHT_FACE_UP,
        RIGHT_FACE_RIGHT = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,
        RIGHT_FACE_DOWN  = GAMEPAD_BUTTON_RIGHT_FACE_DOWN,
        RIGHT_FACE_LEFT  = GAMEPAD_BUTTON_RIGHT_FACE_LEFT,
        LEFT_TRIGGER_1   = GAMEPAD_BUTTON_LEFT_TRIGGER_1,
        LEFT_TRIGGER_2   = GAMEPAD_BUTTON_LEFT_TRIGGER_2,
        RIGHT_TRIGGER_1  = GAMEPAD_BUTTON_RIGHT_TRIGGER_1,
        RIGHT_TRIGGER_2  = GAMEPAD_BUTTON_RIGHT_TRIGGER_2,
        MIDDLE_LEFT      = GAMEPAD_BUTTON_MIDDLE_LEFT,
        MIDDLE           = GAMEPAD_BUTTON_MIDDLE,
        MIDDLE_RIGHT     = GAMEPAD_BUTTON_MIDDLE_RIGHT,
        LEFT_THUMB       = GAMEPAD_BUTTON_LEFT_THUMB,
        RIGHT_THUMB      = GAMEPAD_BUTTON_RIGHT_THUMB,
    };

    /**
     * @brief The gamepad axes.
     */
    enum EGamepadAxis
    {
        LEFT_X        = GAMEPAD_AXIS_LEFT_X,
        LEFT_Y        = GAMEPAD_AXIS_LEFT_Y,
        RIGHT_X       = GAMEPAD_AXIS_RIGHT_X,
        RIGHT_Y       = GAMEPAD_AXIS_RIGHT_Y,
        LEFT_TRIGGER  = GAMEPAD_AXIS_LEFT_TRIGGER,
        RIGHT_TRIGGER = GAMEPAD_AXIS_RIGHT_TRIGGER,
    };

    /**
     * A pair of a gamepad axis and a gamepad index.
     */
    struct GamepadAxisData
    {
        EGamepadAxis axis;
        int          gamepad;
    };

    /**
     * A pair of a gamepad button and a gamepad index.
     */
    struct GamepadButtonData
    {
        EGamepadButton button;
        int            gamepad;
    };

    /**
     * @brief The state of an action.
     */
    enum EActionState
    {
        /// The action has been released since the last update.
        RELEASED,
        /// The action has been pressed since the last update.
        PRESSED,
        /// The action is currently down.
        DOWN,
        /// The action is currently up.
        UP,
    };

    /**
     * @brief An action that can be bound to a key, mouse button, or gamepad button.
     */
    using Action = std::variant<std::monostate, EKey, EMouseButton, GamepadButtonData>;

    /**
     * @brief A positive axis that can be bound to a key, mouse button, or gamepad button.
     * @note This is to bound a button to an axis, which requires a positive and negative axis.
     */
    struct AxisButton
    {
        using AxisType = std::variant<std::monostate, EKey, EMouseButton, GamepadButtonData>;
        AxisType positive;
        AxisType negative;
    };

    /**
     * @brief A positive axis that can be bound to a key, mouse button, or gamepad button.
     */
    struct Axis
    {
        /**
         * @brief An axis that can be bound to a key, mouse button, gamepad button or gamepad axis.
         */
        using AxisType = std::variant<AxisButton, GamepadAxisData>;
        AxisType axis;
        float    dead_zone = 0.0F;
        float    weight    = 1.0F;
    };

    class InputManager
    {
        struct ActionData
        {
            std::vector<Action> actions{};
            EActionState        state;
        };

        struct AxisData
        {
            std::vector<Axis> axes{};
            float             value{};
        };

    private:
        std::unordered_map<std::string, ActionData> actions_{};
        std::unordered_map<std::string, AxisData>   axes_{};

    public:
        void update();

        /**
         * @brief Checks if a key is down.
         * @param key The key.
         * @return True if the key is down, false otherwise.
         */
        [[nodiscard]] bool is_key_down(EKey key) const
        {
            return IsKeyDown(static_cast<int>(key));
        }

        /**
         * @brief Checks if a key is up.
         * @param key The key.
         * @return True if the key is up, false otherwise.
         */
        [[nodiscard]] bool is_key_up(EKey key) const
        {
            return IsKeyUp(static_cast<int>(key));
        }

        /**
         * @brief Checks if a key is pressed.
         * @param key The key.
         * @return True if the key is pressed, false otherwise.
         */
        [[nodiscard]] bool is_key_pressed(EKey key) const
        {
            return IsKeyPressed(static_cast<int>(key));
        }

        /**
         * @brief Checks if a key is released.
         * @param key The key.
         * @return True if the key is released, false otherwise.
         */
        [[nodiscard]] bool is_key_released(EKey key) const
        {
            return IsKeyReleased(static_cast<int>(key));
        }

        /**
         * @brief Checks if a mouse button is down.
         * @param mouse_button The mouse button.
         * @return True if the mouse button is down, false otherwise.
         */
        [[nodiscard]] bool is_mouse_button_down(EMouseButton mouse_button) const
        {
            return IsMouseButtonDown(static_cast<int>(mouse_button));
        }

        /**
         * @brief Checks if a mouse button is up.
         * @param mouse_button The mouse button.
         * @return True if the mouse button is up, false otherwise.
         */
        [[nodiscard]] bool is_mouse_button_up(EMouseButton mouse_button) const
        {
            return IsMouseButtonUp(static_cast<int>(mouse_button));
        }

        /**
         * @brief Checks if a mouse button is pressed.
         * @param mouse_button The mouse button.
         * @return True if the mouse button is pressed, false otherwise.
         */
        [[nodiscard]] bool is_mouse_button_pressed(EMouseButton mouse_button) const
        {
            return IsMouseButtonPressed(static_cast<int>(mouse_button));
        }

        /**
         * @brief Checks if a mouse button is released.
         * @param mouse_button The mouse button.
         * @return True if the mouse button is released, false otherwise.
         */
        [[nodiscard]] bool is_mouse_button_released(EMouseButton mouse_button) const
        {
            return IsMouseButtonReleased(static_cast<int>(mouse_button));
        }

        /**
         * @brief Checks if a gamepad button is down.
         * @param gamepad The gamepad.
         * @param gamepad_button The gamepad button.
         * @return True if the gamepad button is down, false otherwise.
         */
        [[nodiscard]] bool is_gamepad_button_down(int gamepad, EGamepadButton gamepad_button) const
        {
            return IsGamepadButtonDown(gamepad, static_cast<int>(gamepad_button));
        }

        /**
         * @brief Checks if a gamepad button is up.
         * @param gamepad The gamepad.
         * @param gamepad_button The gamepad button.
         * @return True if the gamepad button is up, false otherwise.
         */
        [[nodiscard]] bool is_gamepad_button_up(int gamepad, EGamepadButton gamepad_button) const
        {
            return IsGamepadButtonUp(gamepad, static_cast<int>(gamepad_button));
        }

        /**
         * @brief Checks if a gamepad button is pressed.
         * @param gamepad The gamepad.
         * @param gamepad_button The gamepad button.
         * @return True if the gamepad button is pressed, false otherwise.
         */
        [[nodiscard]] bool is_gamepad_button_pressed(int gamepad, EGamepadButton gamepad_button) const
        {
            return IsGamepadButtonPressed(gamepad, static_cast<int>(gamepad_button));
        }

        /**
         * @brief Checks if a gamepad button is released.
         * @param gamepad The gamepad.
         * @param gamepad_button The gamepad button.
         * @return True if the gamepad button is released, false otherwise.
         */
        [[nodiscard]] bool is_gamepad_button_released(int gamepad, EGamepadButton gamepad_button) const
        {
            return IsGamepadButtonReleased(gamepad, static_cast<int>(gamepad_button));
        }

        /**
         * @brief Gets the value of a gamepad axis.
         * @param gamepad The gamepad.
         * @param gamepad_axis The gamepad axis.
         * @return The value of the gamepad axis.
         */
        [[nodiscard]] float get_gamepad_axis(int gamepad, EGamepadAxis gamepad_axis) const
        {
            return GetGamepadAxisMovement(gamepad, static_cast<int>(gamepad_axis));
        }

        /**
         * @brief Adds an action to the input manager.
         * @param name The name of the action.
         * @param action The action.
         */
        void add_action(std::string_view name, Action action);

        /**
         * @brief Clears an action from the input manager.
         * @param name The name of the action.
         */
        void clear_action(std::string_view name);

        /**
         * @brief Gets the state of an action.
         * @param name The name of the action.
         * @note If the action does not exist, the state will be EActionState::RELEASED.
         * @return The state of the action.
         */
        [[nodiscard]] EActionState get_action(std::string_view name) const;

        /**
         * @brief Checks if an action is down.
         * @param name The name of the action.
         * @return True if the action is down, false otherwise.
         */
        [[nodiscard]] bool is_action_down(std::string_view name) const
        {
            return get_action(name) == EActionState::DOWN || is_action_pressed(name);
        }

        /**
         * @brief Checks if an action is pressed.
         * @note This is called ONLY the frame the action is pressed.
         * @param name The name of the action.
         * @return True if the action is pressed, false otherwise.
         */
        [[nodiscard]] bool is_action_pressed(std::string_view name) const
        {
            return get_action(name) == EActionState::PRESSED;
        }

        /**
         * @brief Checks if an action is released.
         * @note This is called ONLY the frame the action is released.
         * @param name The name of the action.
         * @return True if the action is released, false otherwise.
         */
        [[nodiscard]] bool is_action_released(std::string_view name) const
        {
            return get_action(name) == EActionState::RELEASED;
        }

        /**
         * @brief Checks if an action is up.
         * @param name The name of the action.
         * @return True if the action is up, false otherwise.
         */
        [[nodiscard]] bool is_action_up(std::string_view name) const
        {
            return get_action(name) == EActionState::UP || is_action_released(name);
        }

        /**
         * @brief Adds an axis to the input manager.
         * @param name
         * @param axis
         */
        void add_axis(std::string_view name, Axis axis);

        /**
         * @brief Clears an axis from the input manager.
         * @param name The name of the axis.
         */
        void clear_axis(std::string_view name);

        /**
         * @brief Gets the value of an axis.
         * @param name The name of the axis.
         * @return The value of the axis.
         */
        [[nodiscard]] float get_axis(std::string_view name) const;

        /**
         * @brief Gets the mouse position.
         * @return The mouse position.
         */
        [[nodiscard]] glm::vec2 get_mouse_position() const;

    private:
        /**
         * @brief Processes the actions.
         */
        void process_actions();

        /**
         * @brief Processes the axes.
         */
        void process_axis();
    };
} // namespace missileengine
