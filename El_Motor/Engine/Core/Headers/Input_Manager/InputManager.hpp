#pragma once
#include <iostream>
#include <unordered_map>
#include <array>
#include "InputState.hpp"
#include "Scancode.hpp"
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

        //Clavier - Utilise les scancodes
        void updateKey(Scancode scancode, bool isDown);
        bool isKeyPressed(Scancode scancode) const;
        bool isKeyHeld(Scancode scancode) const;
        bool isKeyReleased(Scancode scancode) const;

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

        // Clavier - Utilise une map pour supporter tous les scancodes
        std::unordered_map<int, InputState> keyStates;
        bool initialized = false;

        //Souris
        std::array<InputState, (size_t)MouseButton::COUNT> mouseStates;

        Maths::Vec2f mousePosition;
        Maths::Vec2f previousMousePosition;
        Maths::Vec2f mouseDelta;
    };
}