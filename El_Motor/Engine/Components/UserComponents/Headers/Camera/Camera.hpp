#pragma once

#include <DirectXMath.h>
#include "Maths/Headers/MVec3.hpp"
#include "Maths/Headers/MQuaternion.hpp"
#include "Maths/Headers/MMatrix4.hpp"
#include "Input_Manager/InputManager.hpp"

class Camera {
protected:
    Maths::Vec3f position;
    Maths::Quatf rotation;

    Maths::Vec3f forward;
    Maths::Vec3f right;
    Maths::Vec3f up;

    float aspectRatio;
    float nearPlane;
    float farPlane;
    float fov;

    float moveSpeed = 0.5f;
    float sensitivity = 0.01f;

    bool firstMousePos = true;

    Maths::Mat4f projection;
    Maths::Mat4f view;
    Maths::Mat4f VP;

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

public:
    Camera();

    virtual void Update(Engine::InputManager& input) = 0;
    float ToRadians(float degree);

    Maths::Mat4f Getprojection() const;
    Maths::Mat4f Getview() const;
    Maths::Mat4f GetVP() const;

};