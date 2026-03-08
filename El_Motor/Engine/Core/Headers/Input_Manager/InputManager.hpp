#pragma once
#include <iostream>
#include <unordered_map>
#include <array>
#include "InputState.hpp"
#include "Scancode.hpp"
#include "MouseButton.hpp"
#include "Maths/Headers/MVec2.hpp"

namespace Engine {

    /// <summary>
    /// Handles keyboard and mouse input.
    /// Tracks key states, mouse buttons, and mouse movement.
    /// </summary>
    class InputManager {
    public:

        InputManager();
        ~InputManager();

        // =========================
        // Global
        // =========================

        /// <summary>
        /// Initializes the input system.
        /// Must be called before using input functions.
        /// </summary>
        void init();

        /// <summary>
        /// Updates the internal input state.
        /// Should be called once per frame.
        /// </summary>
        void update();

        // =========================
        // Keyboard
        // =========================

        /// <summary>
        /// Updates the state of a keyboard key.
        /// </summary>
        /// <param name="scancode">Key scancode</param>
        /// <param name="isDown">Whether the key is pressed</param>
        void updateKey(Scancode scancode, bool isDown);

        /// <summary>
        /// Checks if the key was pressed this frame.
        /// </summary>
        bool isKeyPressed(Scancode scancode) const;

        /// <summary>
        /// Checks if the key is being held down.
        /// </summary>
        bool isKeyHeld(Scancode scancode) const;

        /// <summary>
        /// Checks if the key was released this frame.
        /// </summary>
        bool isKeyReleased(Scancode scancode) const;

        // =========================
        // Mouse
        // =========================

        /// <summary>
        /// Updates the state of a mouse button.
        /// </summary>
        /// <param name="button">Mouse button</param>
        /// <param name="isDown">Whether the button is pressed</param>
        void updateMouseButton(MouseButton button, bool isDown);

        /// <summary>
        /// Checks if the mouse button was pressed this frame.
        /// </summary>
        bool isMousePressed(MouseButton button) const;

        /// <summary>
        /// Checks if the mouse button is being held down.
        /// </summary>
        bool isMouseHeld(MouseButton button) const;

        /// <summary>
        /// Checks if the mouse button was released this frame.
        /// </summary>
        bool isMouseReleased(MouseButton button) const;

        /// <summary>
        /// Sets the current mouse position.
        /// </summary>
        void setMousePosition(Maths::Vec2f pos);

        /// <summary>
        /// Returns the current mouse position.
        /// </summary>
        Maths::Vec2f getMousePosition() const;

        /// <summary>
        /// Returns the delta movement of the mouse since last frame.
        /// </summary>
        Maths::Vec2f getMouseDelta() const;

        /// <summary>
        /// Returns the previous mouse position.
        /// </summary>
        Maths::Vec2f getPreviousMousePosition() const;

    private:

        // =========================
        // Keyboard states
        // =========================

        /// <summary>
        /// Stores the state of each key using scancodes.
        /// </summary>
        std::unordered_map<int, InputState> keyStates;

        /// <summary>
        /// Whether the input manager has been initialized.
        /// </summary>
        bool initialized = false;

        // =========================
        // Mouse states
        // =========================

        /// <summary>
        /// Stores the state of each mouse button.
        /// </summary>
        std::array<InputState, (size_t)MouseButton::COUNT> mouseStates;

        /// <summary>
        /// Current mouse position.
        /// </summary>
        Maths::Vec2f mousePosition;

        /// <summary>
        /// Mouse position from the previous frame.
        /// </summary>
        Maths::Vec2f previousMousePosition;

        /// <summary>
        /// Mouse movement delta (current - previous).
        /// </summary>
        Maths::Vec2f mouseDelta;
    };
}