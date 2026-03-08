#pragma once
#include <iostream>
#include <unordered_map>
#include <array>
#include "InputState.hpp"
#include "Scancode.hpp"
#include "MouseButton.hpp"
#include "Maths/Headers/MVec2.hpp"

namespace Engine {

    /**
     * @brief Handles keyboard and mouse input.
     *
     * Tracks key states, mouse buttons, and mouse movement.
     * Provides functions to query pressed, held, and released states.
     */
    class InputManager {
    public:

        /**
         * @brief Default constructor.
         */
        InputManager();

        /**
         * @brief Destructor.
         */
        ~InputManager();

        // =========================
        // Global
        // =========================

        /**
         * @brief Initializes the input system.
         *
         * Must be called before using input functions.
         */
        void init();

        /**
         * @brief Updates the internal input state.
         *
         * Should be called once per frame.
         */
        void update();

        // =========================
        // Keyboard
        // =========================

        /**
         * @brief Updates the state of a keyboard key.
         * @param scancode Key scancode
         * @param isDown Whether the key is pressed
         */
        void updateKey(Scancode scancode, bool isDown);

        /**
         * @brief Checks if the key was pressed this frame.
         * @param scancode Key scancode
         * @return True if the key was pressed this frame
         */
        bool isKeyPressed(Scancode scancode) const;

        /**
         * @brief Checks if the key is being held down.
         * @param scancode Key scancode
         * @return True if the key is currently held
         */
        bool isKeyHeld(Scancode scancode) const;

        /**
         * @brief Checks if the key was released this frame.
         * @param scancode Key scancode
         * @return True if the key was released this frame
         */
        bool isKeyReleased(Scancode scancode) const;

        // =========================
        // Mouse
        // =========================

        /**
         * @brief Updates the state of a mouse button.
         * @param button Mouse button
         * @param isDown Whether the button is pressed
         */
        void updateMouseButton(MouseButton button, bool isDown);

        /**
         * @brief Checks if the mouse button was pressed this frame.
         * @param button Mouse button
         * @return True if the button was pressed this frame
         */
        bool isMousePressed(MouseButton button) const;

        /**
         * @brief Checks if the mouse button is being held down.
         * @param button Mouse button
         * @return True if the button is currently held
         */
        bool isMouseHeld(MouseButton button) const;

        /**
         * @brief Checks if the mouse button was released this frame.
         * @param button Mouse button
         * @return True if the button was released this frame
         */
        bool isMouseReleased(MouseButton button) const;

        /**
         * @brief Sets the current mouse position.
         * @param pos New mouse position
         */
        void setMousePosition(Maths::Vec2f pos);

        /**
         * @brief Returns the current mouse position.
         * @return Current mouse position
         */
        Maths::Vec2f getMousePosition() const;

        /**
         * @brief Returns the delta movement of the mouse since last frame.
         * @return Mouse movement delta
         */
        Maths::Vec2f getMouseDelta() const;

        /**
         * @brief Returns the previous mouse position.
         * @return Previous mouse position
         */
        Maths::Vec2f getPreviousMousePosition() const;

    private:

        // =========================
        // Keyboard states
        // =========================

        /// @brief Stores the state of each key using scancodes
        std::unordered_map<int, InputState> keyStates;

        /// @brief Whether the input manager has been initialized
        bool initialized = false;

        // =========================
        // Mouse states
        // =========================

        /// @brief Stores the state of each mouse button
        std::array<InputState, (size_t)MouseButton::COUNT> mouseStates;

        /// @brief Current mouse position
        Maths::Vec2f mousePosition;

        /// @brief Mouse position from the previous frame
        Maths::Vec2f previousMousePosition;

        /// @brief Mouse movement delta (current - previous)
        Maths::Vec2f mouseDelta;
    };

} // namespace Engine