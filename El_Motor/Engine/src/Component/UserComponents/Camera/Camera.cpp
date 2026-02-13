#include <DirectXMath.h>
#include <cmath>

#include "Component/UserComponents/Camera/Camera.hpp"
#include "Core/Input_Manager/InputManager.hpp"

using namespace DirectX;

void Camera::RotationUpdate(Engine::InputManager& input)
{
    float dx = input.getMouseDelta().x;
    float dy = input.getMouseDelta().y;

    float mouseSensitivity = sensitivity;

    float yaw = dx * mouseSensitivity;
    float pitch = dy * mouseSensitivity;

    XMVECTOR rightV = XMLoadFloat3(&right);
    XMVECTOR rotV = XMLoadFloat4(&rotation);

    XMVECTOR qYaw = XMQuaternionRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), yaw); // World yaw
    XMVECTOR qPitch = XMQuaternionRotationAxis(rightV, pitch); // Local pitch

    XMVECTOR quaternionMultiply = XMQuaternionMultiply(qPitch, qYaw);

    quaternionMultiply = XMQuaternionMultiply(quaternionMultiply, rotV);

    XMVECTOR newRot = XMQuaternionNormalize(quaternionMultiply);
    XMStoreFloat4(&rotation, newRot);
}

void Camera::FowardUpdate()
{
    XMVECTOR rotV = XMLoadFloat4(&rotation);
    XMVECTOR fwdV = XMVector3Rotate(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotV);
    XMStoreFloat3(&forward, fwdV);
}

void Camera::RightUpdate()
{
    XMVECTOR rotV = XMLoadFloat4(&rotation);
    XMVECTOR rightV = XMVector3Rotate(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rotV);
    XMStoreFloat3(&right, rightV);
}

void Camera::UpUpdate()
{
    XMVECTOR rotV = XMLoadFloat4(&rotation);
    XMVECTOR upV = XMVector3Rotate(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotV);
    XMStoreFloat3(&up, upV);
}

Camera::Camera() : projection(), view(), VP()
{
    position = XMFLOAT3(0.0f, 0.0f, 3.0f);
    rotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

    forward = XMFLOAT3(0.0f, 0.0f, 1.0f);
    right = XMFLOAT3(1.0f, 0.0f, 0.0f);
    up = XMFLOAT3(0.0f, 1.0f, 0.0f);

    aspectRatio = 16.0f / 9.0f;
    nearPlane = 0.01f;
    farPlane = 150.0f;
    fov = XMConvertToRadians(90.0f);
}

///////// CALCUL DE MATRICES //////////

void Camera::ProjectionMatrix()
{
    XMMATRIX proj = XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
    XMStoreFloat4x4(&projection, proj);
}

void Camera::ViewMatrix()
{
    XMVECTOR posV = XMLoadFloat3(&position);
    XMVECTOR fwdV = XMLoadFloat3(&forward);
    XMVECTOR upV = XMLoadFloat3(&up);

    XMMATRIX viewM = XMMatrixLookAtLH(posV, XMVectorAdd(posV, fwdV), upV);
    XMStoreFloat4x4(&view, viewM);
}

void Camera::VPMatrix()
{
    XMMATRIX viewM = XMLoadFloat4x4(&view);
    XMMATRIX projM = XMLoadFloat4x4(&projection);
    XMMATRIX vpM = viewM * projM;
    XMStoreFloat4x4(&VP, vpM);
}

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

    float radYaw = XMConvertToRadians(yaw);
    float radPitch = XMConvertToRadians(pitch);

    XMVECTOR direction = XMVectorSet(cosf(radYaw) * cosf(radPitch), sinf(radPitch), sinf(radYaw) * cosf(radPitch), 0.0f);

    direction = XMVector3Normalize(direction);
    XMStoreFloat3(&forward, direction);
}

void Camera::MoveUpdate(Engine::InputManager& input) {
    // accumulate movement delta, apply once
    DirectX::XMVECTOR moveDelta = DirectX::XMVectorZero();
    DirectX::XMVECTOR fwdV = XMLoadFloat3(&forward);
    DirectX::XMVECTOR rightV = XMLoadFloat3(&right);
    DirectX::XMVECTOR upV = XMLoadFloat3(&up);

    if (input.isKeyPressed(Engine::KeyCode::Z))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(fwdV, moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::S))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(fwdV, -moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::Q))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(rightV, moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::D))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(rightV, -moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::SPACE))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(upV, moveSpeed));
    if (input.isKeyPressed(Engine::KeyCode::ESCAPE))
        moveDelta = DirectX::XMVectorAdd(moveDelta, DirectX::XMVectorScale(upV, -moveSpeed));

    // apply movement if any
    if (!DirectX::XMVector3Equal(moveDelta, DirectX::XMVectorZero()))
    {
        DirectX::XMVECTOR posV = DirectX::XMLoadFloat3(&position);
        posV = DirectX::XMVectorAdd(posV, moveDelta);
        DirectX::XMStoreFloat3(&position, posV);
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

XMFLOAT4X4 Camera::Getprojection() const
{
    return projection;
}

XMFLOAT4X4 Camera::Getview() const
{
    return view;
}

XMFLOAT4X4 Camera::GetVP() const
{
    return VP;
}
