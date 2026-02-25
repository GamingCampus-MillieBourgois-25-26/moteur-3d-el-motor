//#include <DirectXMath.h>
//#include <cmath>
//
//#include "Camera/Camera.hpp"
//#include "Input_Manager/InputManager.hpp"
//
//using namespace DirectX;
//
//void Camera::RotationUpdate(Engine::InputManager& input)
//{
//    float dx = input.getMouseDelta().x;
//    float dy = input.getMouseDelta().y;
//
//    float mouseSensitivity = sensitivity;
//
//    float yaw = dx * mouseSensitivity;
//    float pitch = dy * mouseSensitivity;
//
//    glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0.0f, 1.0f, 0.0f));
//    glm::quat qPitch = glm::angleAxis(pitch, right);
//
//    rotation = qPitch * qYaw * rotation;
//}
//
//void Camera::FowardUpdate(){ forward = glm::vec3(0.0f, 0.0f, 1.0f) * rotation; }
//
//void Camera::RightUpdate(){ right = glm::vec3(1.0f, 0.0f, 0.0f) * rotation; }
//
//void Camera::UpUpdate(){ up = glm::vec3(0.0f, 1.0f, 0.0f) * rotation; }
//
//Camera::Camera() : projection(), view(), VP()
//{
//    position = glm::vec3(0.0f, 0.0f, 3.0f);
//    rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
//
//    forward = glm::vec3(0.0f, 0.0f, 1.0f);
//    right = glm::vec3(1.0f, 0.0f, 0.0f);
//    up = glm::vec3(0.0f, 1.0f, 0.0f);
//
//    aspectRatio = 16.0f / 9.0f;
//    nearPlane = 0.01f;
//    farPlane = 150.0f;
//
//    fov = glm::radians(90.0f);
//}
//
/////////// CALCUL DE MATRICES //////////
//
//void Camera::ProjectionMatrix(){ glm::mat4x4 proj = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane); }
//
//void Camera::ViewMatrix(){ glm::mat4x4 viewM = glm::lookAtLH(position, position + forward, up); }
//
//void Camera::VPMatrix(){ glm::mat4x4 viewMP = view * projection; }
//
//void Camera::MouseUpdate(Engine::InputManager& input)
//{
//    // lastxy ; xyoffset ; sensitivity ; fistPos ; 
//    float Xpos = input.getMousePosition().x;
//    float Ypos = input.getMousePosition().y;
//
//    static float lastX = 0.0f;
//    static float lastY = 0.0f;
//    static float yaw = 0.0f;
//    static float pitch = 0.0f;
//
//    if (firstMousePos)
//    {
//        lastX = Xpos;
//        lastY = Ypos;
//        firstMousePos = false;
//    }
//
//    float XOffset = Xpos - lastX;
//    float YOffset = lastY - Ypos;
//
//    lastX = Xpos;
//    lastY = Ypos;
//
//    XOffset *= sensitivity;
//    YOffset *= sensitivity;
//
//    yaw += XOffset;
//    pitch += YOffset;
//
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//	float radYaw = glm::radians(yaw);
//    float radPitch = glm::radians(pitch);
//
//	glm::vec3 direction = glm::vec3(cosf(radYaw) * cosf(radPitch), sinf(radPitch), sinf(radYaw) * cosf(radPitch));
//	direction = glm::normalize(direction);
//
//}
//
//void Camera::MoveUpdate(Engine::InputManager& input) {
//    // accumulate movement delta, apply once
//    
//    glm::vec3 moveDelta = glm::vec3(0.0f, 0.0f, 0.0f);
//
//    if (input.isKeyPressed(Engine::KeyCode::Z))
//		moveDelta = moveDelta + forward * moveSpeed;
//    if (input.isKeyPressed(Engine::KeyCode::S))
//        moveDelta = moveDelta + forward * -moveSpeed;
//    if (input.isKeyPressed(Engine::KeyCode::Q))
//		moveDelta = moveDelta + right * moveSpeed;
//    if (input.isKeyPressed(Engine::KeyCode::D))
//        moveDelta = moveDelta + right * -moveSpeed;
//    
//    if (moveDelta == glm::vec3(0.0f, 0.0f, 0.0f)) {
//		position = position + moveDelta;
//    }
//
//    if (input.isMousePressed(Engine::MouseButton::Left))
//    {
//        MouseUpdate(input);
//    }
//}
//
//void Camera::GlobalUpdate(Engine::InputManager& input)
//{
//    FowardUpdate();
//    RightUpdate();
//    UpUpdate();
//    MouseUpdate(input);
//    MoveUpdate(input);
//    ProjectionMatrix();
//    ViewMatrix();
//    VPMatrix();
//}
//
//////////// GETTERS //////////
//
//glm::mat4x4 Camera::Getprojection() const { return projection; }
//
//glm::mat4x4 Camera::Getview() const { return view; }
//
//glm::mat4x4 Camera::GetVP() const { return VP; }