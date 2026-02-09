#include "EditorCamera.hpp"

EditorCamera::EditorCamera() : Camera() {}

void EditorCamera::Update(Engine::InputManager& input) {
	ViewMatrix();
	ProjectionMatrix();
	VPMatrix();

	// POSITION & ROTATION //   
			// float speed = moveSpeed * dt; SI DELTATIME

	if (input.isKeyPressed('Z')) {
		position += forward * moveSpeed;
	}
	if (input.isKeyPressed('S')) {
		position -= forward * moveSpeed;
	}
	if (input.isKeyPressed('Q')) {
		position += right * moveSpeed;
	}
	if (input.isKeyPressed('D')) {
		position -= right * moveSpeed;
	}
	if (input.isKeyPressed('A')) {
		position += up * moveSpeed;
	}
	if (input.isKeyPressed('E')) {
		position -= up * moveSpeed;
	}

	/*if (input.isMousePressed('Left')) {    A VOIR
		
	}*/
}