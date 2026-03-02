#pragma once
#include <iostream>
#include <array>
#include "InputState.hpp"
#include "KeyCode.hpp"
#include "MouseButton.hpp"
#include "Maths/Headers/MVec2.hpp"

namespace Engine{
    class InputManager {
    public:

        InputManager();

        ~InputManager();


        //Global
        void init();
        void update();

        //Clavier
        void updateKey(KeyCode key, bool isDown);
        bool isKeyPressed(KeyCode key) const;
        bool isKeyHeld(KeyCode key) const;
        bool isKeyReleased(KeyCode key) const;

        //Souris
        void updateMouseButton(MouseButton button, bool isDown);
        bool isMousePressed(MouseButton button) const;
        bool isMouseHeld(MouseButton button) const;
        bool isMouseReleased(MouseButton button) const;

        void setMousePosition(Maths::Vec2f pos);
        Maths::Vec2f getMousePosition() const;
        Maths::Vec2f getMouseDelta() const;
        Maths::Vec2f getPreviousMousePosition() const;


    private:

        //clavier
        std::array<InputState, (size_t)KeyCode::COUNT> keyStates;
        bool initialized = false;

        //Souris
        std::array<InputState, (size_t)MouseButton::COUNT> mouseStates;

        Maths::Vec2f mousePosition;
        Maths::Vec2f previousMousePosition;
        Maths::Vec2f mouseDelta;
    };
}