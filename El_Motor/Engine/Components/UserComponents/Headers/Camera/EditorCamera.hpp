#pragma once
#include "Camera.hpp"

/// <summary>
/// Camera used inside the editor environment.
/// This camera allows free movement and rotation in the scene
/// to inspect and manipulate objects during editing.
/// </summary>
class EditorCamera : public Camera {
public:

	/// <summary>
	/// Default constructor for the editor camera.
	/// Initializes camera parameters specific to the editor.
	/// </summary>
	EditorCamera();

	/// <summary>
	/// Updates the editor camera state.
	/// Handles movement, mouse rotation, and matrix updates
	/// using the input manager.
	/// </summary>
	/// <param name="input">Input manager used to control the camera</param>
	void Update(Engine::InputManager& input) override;
};