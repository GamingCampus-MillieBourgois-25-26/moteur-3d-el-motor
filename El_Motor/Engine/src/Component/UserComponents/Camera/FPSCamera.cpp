#include "Component/UserComponents/Camera/FPSCamera.hpp"
#include "Component/UserComponents/Camera/Camera.hpp"

FPSCamera::FPSCamera() : Camera() {}

void FPSCamera::Update(Engine::InputManager& input)
{
    GlobalUpdate(input);
    MouseUpdate(input);

    // POSITION & ROTATION //   
    // float speed = moveSpeed * dt; SI DELTATIME

    /*switch (input.isKeyPressed(Engine::KeyCode))
    {
    case 'Z':
        position += forward * moveSpeed;
        break;
    case 'S':
        position -= forward * moveSpeed;
        break;
    case 'Q':
        position += right * moveSpeed;
        break;
    case 'D':
        position -= right * moveSpeed;
        break;
    }*/
}
