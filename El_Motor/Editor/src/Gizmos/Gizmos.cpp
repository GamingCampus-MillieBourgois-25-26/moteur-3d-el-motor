#include "Gizmos/Gizmos.hpp"

void Editor::Gizmo::Draw() {
	if (ImGuizmo::IsUsingAny()) { // a gizmo in use
		
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