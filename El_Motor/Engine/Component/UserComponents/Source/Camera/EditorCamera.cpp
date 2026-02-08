#include "EditorCamera.hpp"

EditorCamera::EditorCamera() : Camera() {}

void EditorCamera::Update() {
	ViewMatrix();
	ProjectionMatrix();
	VPMatrix();

	// POSITION & ROTATION // 
	

}