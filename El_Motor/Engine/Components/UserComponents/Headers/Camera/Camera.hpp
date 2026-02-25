#pragma once

#include <DirectXMath.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include "Input_Manager/InputManager.hpp"

class Camera {
protected:
    glm::vec3 position;
    glm::quat rotation;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    float aspectRatio;
    float nearPlane;
    float farPlane;
    float fov;

    float moveSpeed = 1.f;
    float sensitivity = 0.01f;

    bool firstMousePos = true;

    glm::mat4x4 projection;
    glm::mat4x4 view;
    glm::mat4x4 VP;

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

    glm::mat4x4 Getprojection() const;
    glm::mat4x4 Getview() const;
    glm::mat4x4 GetVP() const;

public:
    Camera();

    virtual void Update(Engine::InputManager& input) = 0;
};