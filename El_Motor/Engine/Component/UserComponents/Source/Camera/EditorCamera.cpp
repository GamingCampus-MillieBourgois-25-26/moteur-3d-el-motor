#include "Camera/EditorCamera.hpp"

EditorCamera::EditorCamera() {}

void EditorCamera::Update(Engine::InputManager& input)
{
    GlobalUpdate(input);
}