#pragma once

#include <DirectXMath.h>

#include "Core/Input_Manager/KeyCode.hpp"
#include "Core/Input_Manager/MouseButton.hpp"
#include "Core/Input_Manager/InputManager.hpp"

class Camera
{
protected:
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 rotation;

    DirectX::XMFLOAT3 forward;
    DirectX::XMFLOAT3 right;
    DirectX::XMFLOAT3 up;

    float aspectRatio;
    float nearPlane;
    float farPlane;
    float fov;

    float moveSpeed = 1.f;
    float sensitivity = 0.01f;

    bool firstMousePos = true;

    DirectX::XMFLOAT4X4 projection;
    DirectX::XMFLOAT4X4 view;
    DirectX::XMFLOAT4X4 VP;

    void RotationUpdate(Engine::InputManager& input);
    void FowardUpdate();
    void RightUpdate();
    void UpUpdate();

    void ProjectionMatrix(); // Persepective
    void ViewMatrix(); // World to Camera
    void VPMatrix(); // Projection * View

    void MouseUpdate(Engine::InputManager& input);
    void MoveUpdate(Engine::InputManager& input);
    void GlobalUpdate(Engine::InputManager& input);

    //////// GETTERS //////////

    DirectX::XMFLOAT4X4 Getprojection() const;
    DirectX::XMFLOAT4X4 Getview() const;
    DirectX::XMFLOAT4X4 GetVP() const;

public:
    Camera();

    virtual void Update(Engine::InputManager& input) = 0;
};
