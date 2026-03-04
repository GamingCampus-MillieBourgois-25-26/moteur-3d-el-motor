#pragma once
 
#include <ImGuizmo.h>

#include "Maths/Headers/MMatrix4.hpp"
#include "Camera/Camera.hpp"

/*enum GizmoType {
	Translate,
	Rotate,
	Scale,
	None
};

enum GizmoAxis {
	None,
	X,
	Y,
	Z
};*/

namespace Editor {
	class Gizmo {
	public:
		Gizmo() = default;
		~Gizmo() = default;

		void Draw(const Camera& camera);
		void Update();

	private:
		Maths::Mat4f m_projection;
		Maths::Mat4f m_transform;
		Maths::Mat4f m_view;

		bool isSelected = false;
		int currentGizmo;
		int currentAxis;
	};
}