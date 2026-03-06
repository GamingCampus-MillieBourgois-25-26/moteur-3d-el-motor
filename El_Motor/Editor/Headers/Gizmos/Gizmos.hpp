#pragma once

#include <External/ImGui/includes/ImGuizmo/ImGuizmo.h>

#include "Maths/Headers/MMatrix4.hpp"
#include "Camera/Camera.hpp"

namespace Editor {
	class Gizmo {
	public:
		Gizmo() = default;
		~Gizmo() = default;

		void Draw(Camera& camera);
		void Update();

	private:
		bool isSelected = false;
		ImGuizmo::OPERATION mCurrentOperation = ImGuizmo::OPERATION::TRANSLATE;
		ImGuizmo::COLOR mCurrentAxis;
		ImGuizmo::MODE mCurrentMode = ImGuizmo::MODE::LOCAL;
	};
}