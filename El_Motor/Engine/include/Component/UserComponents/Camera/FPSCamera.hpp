#pragma once

#include "Camera.hpp"
#include "Core/Input_Manager/InputManager.hpp"

class FPSCamera : public Camera
{
public:
    FPSCamera();

    void Update(Engine::InputManager& input) override;
};
