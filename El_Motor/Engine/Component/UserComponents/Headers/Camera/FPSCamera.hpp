#pragma once
#include "Camera.hpp"

class FPSCamera : public Camera {
public:
	FPSCamera();

	void Update(Engine::InputManager& input) override;
};