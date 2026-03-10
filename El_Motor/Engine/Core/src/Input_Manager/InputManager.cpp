#include "Input_Manager/InputManager.hpp"
#include <GLFW/glfw3.h>

Engine::InputManager::InputManager() {
    mouseStates.fill(InputState::Up);
    mousePosition = { 0.f, 0.f };
    previousMousePosition = { 0.f, 0.f };
    mouseDelta = { 0.f, 0.f };
}

Engine::InputManager::~InputManager() {}

void Engine::InputManager::init() {
    if (initialized == true) return;
    initialized = true;

    keyStates.clear();
    mouseStates.fill(InputState::Up);
    mousePosition = { 0.f, 0.f };
    previousMousePosition = { 0.f, 0.f };
}

void Engine::InputManager::updateKey(Scancode scancode, bool isDown) {
    int scancodeValue = static_cast<int>(scancode);
    
    // Initialiser la touche si elle n'existe pas
    if (keyStates.find(scancodeValue) == keyStates.end()) {
        keyStates[scancodeValue] = InputState::Up;
    }
    
    InputState& state = keyStates[scancodeValue];

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
    // Transition des états des touches
    for (auto& [scancode, state] : keyStates) {
        if (state == InputState::Pressed)
            state = InputState::Held;
        else if (state == InputState::Released)
            state = InputState::Up;
    }

    // Calcul du delta souris
    mouseDelta.m_x = mousePosition.m_x - previousMousePosition.m_x;
    mouseDelta.m_y = mousePosition.m_y - previousMousePosition.m_y;

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


// Fonctions publiques - Clavier

bool Engine::InputManager::isKeyPressed(Scancode scancode) const {
    int scancodeValue = static_cast<int>(scancode);
    auto it = keyStates.find(scancodeValue);
    return it != keyStates.end() && it->second == InputState::Pressed;
}

bool Engine::InputManager::isKeyHeld(Scancode scancode) const {
    int scancodeValue = static_cast<int>(scancode);
    auto it = keyStates.find(scancodeValue);
    return it != keyStates.end() && it->second == InputState::Held;
}

bool Engine::InputManager::isKeyReleased(Scancode scancode) const {
    int scancodeValue = static_cast<int>(scancode);
    auto it = keyStates.find(scancodeValue);
    return it != keyStates.end() && it->second == InputState::Released;
}


// Fonctions publiques - Souris

bool Engine::InputManager::isMousePressed(MouseButton button) const {
    return mouseStates[(size_t)button] == InputState::Pressed;
}

bool Engine::InputManager::isMouseHeld(MouseButton button) const {
    return mouseStates[(size_t)button] == InputState::Held;
}

bool Engine::InputManager::isMouseReleased(MouseButton button) const {
    return mouseStates[(size_t)button] == InputState::Released;
}

void Engine::InputManager::setMousePosition(Maths::Vec2f pos) {
    mousePosition = pos;
}

Maths::Vec2f Engine::InputManager::getMousePosition() const { return mousePosition; }

Maths::Vec2f Engine::InputManager::getMouseDelta() const { return mouseDelta; }

Maths::Vec2f Engine::InputManager::getPreviousMousePosition() const { return previousMousePosition; }
