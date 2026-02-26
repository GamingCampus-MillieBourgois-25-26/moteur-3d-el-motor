#include "Camera/Camera.hpp"
#include "Input_Manager/InputManager.hpp"

float ToRadians(float degree) {
    return degree * Maths::Quatf::PI / 180;
}

void Camera::RotationUpdate(Engine::InputManager& input)
{
    float dx = input.getMouseDelta().x;
    float dy = input.getMouseDelta().y;

    float mouseSensitivity = sensitivity;

    float yaw = dx * mouseSensitivity;
    float pitch = dy * mouseSensitivity;

    Maths::Quatf qYaw = Maths::Quatf::AngleAxis(yaw, Maths::Quatf(0.0f, 1.0f, 0.0f, 0.0f));

    Maths::Quatf QuatR = Maths::Quatf::FromEuler(right);
    Maths::Quatf qPitch = Maths::Quatf::AngleAxis(pitch, QuatR);

    rotation = qPitch * qYaw * rotation;
}

void Camera::FowardUpdate() { forward = Maths::Quatf::MulltiplyQuatVec(Maths::Vec3f(0.0f, 0.0f, 1.0f), rotation); }

void Camera::RightUpdate(){ right = Maths::Quatf::MulltiplyQuatVec(Maths::Vec3f(1.0f, 0.0f, 0.0f), rotation); }

void Camera::UpUpdate(){ up = Maths::Quatf::MulltiplyQuatVec(Maths::Vec3f(0.0f, 1.0f, 0.0f), rotation); }

Camera::Camera() : projection(), view(), VP()
{
    position = Maths::Vec3f(0.0f, 0.0f, 3.0f);
    rotation = Maths::Quatf(0.0f, 0.0f, 0.0f, 1.0f);

    forward = Maths::Vec3f(0.0f, 0.0f, 1.0f);
    right = Maths::Vec3f(1.0f, 0.0f, 0.0f);
    up = Maths::Vec3f(0.0f, 1.0f, 0.0f);

    aspectRatio = 16.0f / 9.0f;
    nearPlane = 0.01f;
    farPlane = 150.0f;

    fov = ToRadians(90.0f);
}

///////// CALCUL DE MATRICES //////////

void Camera::ProjectionMatrix(){ Maths::Mat4f proj = Maths::Mat4f::Perspective4x4(fov, aspectRatio, nearPlane, farPlane); }

void Camera::ViewMatrix(){ Maths::Mat4f viewM = Maths::Mat4f::LookAt4x4(position, position + forward, up); }

void Camera::VPMatrix(){ Maths::Mat4f viewMP = view * projection; }

void Camera::MouseUpdate(Engine::InputManager& input)
{
    // lastxy ; xyoffset ; sensitivity ; fistPos ; 
    float Xpos = input.getMousePosition().x;
    float Ypos = input.getMousePosition().y;

    static float lastX = 0.0f;
    static float lastY = 0.0f;
    static float yaw = 0.0f;
    static float pitch = 0.0f;

    if (firstMousePos)
    {
        lastX = Xpos;
        lastY = Ypos;
        firstMousePos = false;
    }

    float XOffset = Xpos - lastX;
    float YOffset = lastY - Ypos;

    lastX = Xpos;
    lastY = Ypos;

    XOffset *= sensitivity;
    YOffset *= sensitivity;

    yaw += XOffset;
    pitch += YOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

	float radYaw = ToRadians(yaw);
    float radPitch = ToRadians(pitch);

	Maths::Vec3f direction = Maths::Vec3f(cosf(radYaw) * cosf(radPitch), sinf(radPitch), sinf(radYaw) * cosf(radPitch));
	direction = direction.Normalized();

}

void Camera::MoveUpdate(Engine::InputManager& input) {
    // accumulate movement delta, apply once
    
    Maths::Vec3f moveDelta = Maths::Vec3f(0.0f, 0.0f, 0.0f);

    if (input.isKeyPressed(Engine::KeyCode::Z))
		moveDelta = moveDelta + forward * moveSpeed;
    if (input.isKeyPressed(Engine::KeyCode::S))
        moveDelta = moveDelta + forward * -moveSpeed;
    if (input.isKeyPressed(Engine::KeyCode::Q))
		moveDelta = moveDelta + right * moveSpeed;
    if (input.isKeyPressed(Engine::KeyCode::D))
        moveDelta = moveDelta + right * -moveSpeed;
    
    if (moveDelta == Maths::Vec3f(0.0f, 0.0f, 0.0f)) {
		position = position + moveDelta;
    }

    if (input.isMousePressed(Engine::MouseButton::Left))
    {
        MouseUpdate(input);
    }
}

void Camera::GlobalUpdate(Engine::InputManager& input)
{
    FowardUpdate();
    RightUpdate();
    UpUpdate();
    MouseUpdate(input);
    MoveUpdate(input);
    ProjectionMatrix();
    ViewMatrix();
    VPMatrix();
}

////////// GETTERS //////////

Maths::Mat4f Camera::Getprojection() const { return projection; }

Maths::Mat4f Camera::Getview() const { return view; }

Maths::Mat4f Camera::GetVP() const { return VP; }