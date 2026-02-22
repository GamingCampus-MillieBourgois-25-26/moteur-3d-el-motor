#pragma once

#include <DirectXMath.h>
#include "MathLibrary/Vector3D.h"
#include "MathLibrary/Quaternions.h"  
#include "MathLibrary/Matrice4x4.h"
#include "Input_Manager/InputManager.hpp"

class Camera {
protected:
    Maths::Vct3D<float> position;
    Maths::Quat<float> rotation;

    Maths::Vct3D<float> forward;
    Maths::Vct3D<float> right;
    Maths::Vct3D<float> up;

    float aspectRatio;
    float nearPlane;
    float farPlane;
    float fov;

    float moveSpeed = 1.f;
    float sensitivity = 0.01f;

    bool firstMousePos = true;

    Maths::Matrix4<float> projection;
    Maths::Matrix4<float> view;
    Maths::Matrix4<float> VP;

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

    Maths::Matrix4<float> Getprojection() const;
    Maths::Matrix4<float> Getview() const;
    Maths::Matrix4<float> GetVP() const;

public:
    Camera();

    virtual void Update(Engine::InputManager& input) = 0;
	float ConvertToRadians(float degrees) const { return degrees * (Maths::Quat<float>::PI / 180.0f); }
};