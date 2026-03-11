#include "Gizmos/Gizmos.hpp"

void Editor::Gizmo::Draw(Camera& camera)
{
    ImGuizmo::BeginFrame();

    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();

    if (isSelected)
    {
       /* ImGuizmo::Manipulate(
            Maths::Mat4f::value_ptr(camera.GetView()),
            Maths::Mat4f::value_ptr(camera.GetProjection()),
            mCurrentOperation,
            mCurrentMode,
            Maths::Mat4f::value_ptr(transform) transform of the selected object
        );*/

		// decompose and update the transform of the selected object

        /*if (ImGuizmo::IsUsing())
        {
            float translation[3];
            float rotation[3];
            float scale[3];

            ImGuizmo::DecomposeMatrixToComponents(
                Maths::Mat4f::value_ptr(transform),
                translation,
                rotation,
                scale
            );

            auto* t = selectedObject->GetTransform();

            t->SetPosition(Maths::Vec3f(translation[0], translation[1], translation[2]));
            Maths::Quatf quat = Maths::Quatf::FromEulerDegrees(rotation[0], rotation[1], rotation[2]);
            t->SetRotation(quat);
            t->SetScale(Maths::Vec3f(scale[0], scale[1], scale[2]));;
        }*/
    }
}

void Editor::Gizmo::Update() {
	if (ImGui::IsKeyPressed(ImGuiKey_T))
		mCurrentOperation = ImGuizmo::TRANSLATE;

	if (ImGui::IsKeyPressed(ImGuiKey_R))
		mCurrentOperation = ImGuizmo::ROTATE;

	if (ImGui::IsKeyPressed(ImGuiKey_G))
		mCurrentOperation = ImGuizmo::SCALE;
}