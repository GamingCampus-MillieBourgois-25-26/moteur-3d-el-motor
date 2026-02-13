#pragma once
#include "Camera.hpp"

class EditorCamera : public Camera {
	public:
	EditorCamera();

	void Update(Engine::InputManager &input) override;
};