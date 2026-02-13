#include "Component/UserComponents/Camera/EditorCamera.hpp"
#include "Component/UserComponents/Camera/Camera.hpp"



EditorCamera::EditorCamera() {}

void EditorCamera::Update(Engine::InputManager& input)
{
    GlobalUpdate(input);
}
