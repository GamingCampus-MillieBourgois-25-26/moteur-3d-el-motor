#include "Gizmos/Gizmos.hpp"

void Editor::Gizmo::Draw(Camera& camera)
{
	ImGuizmo::BeginFrame();

	if(isSelected){
		ImGuizmo::Manipulate(
			Maths::Mat4f::value_ptr(camera.GetView()),
			Maths::Mat4f::value_ptr(camera.GetProjection()),
			mCurrentOperation,
			mCurrentMode,
			Maths::Mat4f::value_ptr(transform)
		);
	}
}

void Editor::Gizmo::Update() {
	// si press T ou isSelected
			// mCurrentOperation = ImGuizmo::OPERATION::TRANSLATE;
			// MovingState = true

		// si press R ou isSelected
			// mCurrentOperation = ImGuizmo::OPERATION::ROTATE;
			// MovingState = true

		// si press G ou isSelected
			// mCurrentOperation = ImGuizmo::OPERATION::SCALE;
			// MovingState = true
}