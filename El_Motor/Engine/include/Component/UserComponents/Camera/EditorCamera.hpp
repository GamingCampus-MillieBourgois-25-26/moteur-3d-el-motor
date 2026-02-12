#pragma once

#include "Camera.hpp"

#include "Core/Input_Manager/InputManager.hpp"

class EditorCamera : public Camera
{
public:
    EditorCamera();

    void Update(Engine::InputManager& input) override;
};
