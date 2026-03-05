#pragma once

#include <External/ImGui/includes/ImGuizmo/ImGuizmo.h>

#include "Maths/Headers/MMatrix4.hpp"
#include "Camera/Camera.hpp"

namespace Editor {
	class Gizmo {
	public:
		Gizmo() = default;
		~Gizmo() = default;

		void Draw();
		void Update();

	private:
		Maths::Mat4f mProjection;
		Maths::Mat4f mTransform;
		Maths::Mat4f mView;

		bool isSelected = false;
		ImGuizmo::OPERATION mCurrentOperation;
		ImGuizmo::COLOR mCurrentAxis;
		ImGuizmo::MODE mCurrentMode;
	};
}