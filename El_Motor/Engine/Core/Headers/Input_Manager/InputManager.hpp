#pragma once
#include <iostream>
#include <array>
#include "InputState.hpp"
#include "KeyCode.hpp"
#include "MouseButton.hpp"
#include "Vec2.hpp"
namespace Engine

{
class InputManager {

public:

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

    void setMousePosition(Vec2 pos);
    Vec2 getMousePosition() const;
    Vec2 getMouseDelta() const;
    Vec2 getPreviousMousePosition() const;


private:

    //clavier
    std::array<InputState, (size_t)KeyCode::COUNT> keyStates;
    bool initialized = false;

    //Souris
    std::array<InputState, (size_t)MouseButton::COUNT> mouseStates;

    Vec2 mousePosition;
    Vec2 previousMousePosition;
    Vec2 mouseDelta;
};
}