#include "FPSCamera.hpp"

FPSCamera::FPSCamera() : Camera() {}

void FPSCamera::Update(Engine::InputManager& input) {
	GlobalUpdate();
	MouseUpdate();

	// POSITION & ROTATION //   
			// float speed = moveSpeed * dt; SI DELTATIME

	switch (input.isKeyPressed(Engine::KeyCode)) {
	case 'Z':
		position += forward * moveSpeed;
		break;
	case 'S':
		position -= forward * moveSpeed;
		break;
	case 'Q':
		position += right * moveSpeed;
		break;
	case 'D':
		position -= right * moveSpeed;
		break;
	}
}