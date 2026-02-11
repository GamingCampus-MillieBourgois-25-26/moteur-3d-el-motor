#include "EditorCamera.hpp"

EditorCamera::EditorCamera() : Camera() {}

void EditorCamera::Update(Engine::InputManager& input) {
	GlobalUpdate();

	// POSITION & ROTATION //   
			// float speed = moveSpeed * dt; SI DELTATIME

	switch (input.isKeyPressed(Engine::KeyCode)) {
	case 'Z' :
		position += forward * moveSpeed;
		break;
	case 'S' :
		position -= forward * moveSpeed;
		break;
	case 'Q' :
		position += right * moveSpeed;
		break;
	case 'D' :
		position -= right * moveSpeed;
		break;
	case 'A' :
		position += up * moveSpeed;
		break;
	case 'E' :
		position -= up * moveSpeed;
		break;
	}

	if (input.isMousePressed('Left')) {
		MouseUpdate();
	}
}