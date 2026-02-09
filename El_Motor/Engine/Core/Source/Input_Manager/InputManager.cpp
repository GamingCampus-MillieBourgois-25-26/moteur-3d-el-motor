#include "../Core/Headers/Input_Manager/InputManager.hpp"


void Engine::InputManager::init() {
    if (initialized == true) return;
    initialized = true;

    keyStates.fill(InputState::Up);
    mouseStates.fill(InputState::Up);
    mousePosition = { 0.f, 0.f };
    previousMousePosition = { 0.f, 0.f };
}
void Engine::InputManager::updateKey(KeyCode key, bool isDown) {
    InputState& state = keyStates[(size_t)key];

    if (isDown) {
        if (state == InputState::Up || state == InputState::Released)
            state = InputState::Pressed;
        else
            state = InputState::Held;
    }
    else {
        if (state == InputState::Held || state == InputState::Pressed)
            state = InputState::Released;
        else
            state = InputState::Up;
    }
}
void Engine::InputManager::update() {
    for (auto& state : keyStates) {
        if (state == InputState::Pressed)
            state = InputState::Held;
        else if (state == InputState::Released)
            state = InputState::Up;
    }

    mouseDelta.x = mousePosition.x - previousMousePosition.x;
    mouseDelta.y = mousePosition.y - previousMousePosition.y;

    previousMousePosition = mousePosition;
}




void Engine::InputManager::updateMouseButton(MouseButton button, bool isDown) {
    InputState& state = mouseStates[(size_t)button];

    if (isDown) {
        if (state == InputState::Up || state == InputState::Released)
            state = InputState::Pressed;
        else
            state = InputState::Held;
    }
    else {
        if (state == InputState::Held || state == InputState::Pressed)
            state = InputState::Released;
        else
            state = InputState::Up;
    }
}


// Fonctions publiques


//Clavier
bool  Engine::InputManager::isKeyPressed(KeyCode key) const {
    return keyStates[(size_t)key] == InputState::Pressed;
}

bool  Engine::InputManager::isKeyHeld(KeyCode key) const {
    return keyStates[(size_t)key] == InputState::Held;
}

bool  Engine::InputManager::isKeyReleased(KeyCode key) const {
    return keyStates[(size_t)key] == InputState::Released;
}



//Souris
bool Engine::InputManager::isMousePressed(MouseButton button) const {
    return mouseStates[(size_t)button] == InputState::Pressed;
}
bool Engine::InputManager::isMouseHeld(MouseButton button) const {
    return mouseStates[(size_t)button] == InputState::Held;
}
bool Engine::InputManager::isMouseReleased(MouseButton button) const {
    return mouseStates[(size_t)button] == InputState::Released;
}

void Engine::InputManager::setMousePosition(Vec2 pos) {
    mousePosition = pos;
}

Engine::Vec2 Engine::InputManager::getMousePosition() const { return mousePosition; }

Engine::Vec2 Engine::InputManager::getMouseDelta() const {
    return mouseDelta;
}