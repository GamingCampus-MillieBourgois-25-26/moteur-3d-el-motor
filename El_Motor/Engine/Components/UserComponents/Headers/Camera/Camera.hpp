#pragma once

#include <DirectXMath.h>
#include "Maths/Headers/MVec3.hpp"
#include "Maths/Headers/MQuaternion.hpp"
#include "Maths/Headers/MMatrix4.hpp"
#include "Input_Manager/InputManager.hpp"

/// <summary>
/// Base camera class used to handle camera transformations,
/// movement, and view/projection matrix generation.
/// This class provides common camera functionality and
/// must be inherited to implement specific camera behaviors.
/// </summary>
class Camera {
protected:

    /// Position of the camera in world space
    Maths::Vec3f position;

    /// Rotation of the camera represented as a quaternion
    Maths::Quatf rotation;

    /// Forward direction vector of the camera
    Maths::Vec3f forward;

    /// Right direction vector of the camera
    Maths::Vec3f right;

    /// Up direction vector of the camera
    Maths::Vec3f up;

    /// Aspect ratio of the camera viewport
    float aspectRatio;

    /// Near clipping plane distance
    float nearPlane;

    /// Far clipping plane distance
    float farPlane;

    /// Field of view in degrees
    float fov;

    /// Camera movement speed
    float moveSpeed = 0.5f;

    /// Mouse sensitivity used for camera rotation
    float sensitivity = 0.01f;

    /// Indicates whether the first mouse position has been recorded
    bool firstMousePos = true;

    /// Projection matrix used for perspective transformation
    Maths::Mat4f projection;

    /// View matrix used to transform world coordinates into camera space
    Maths::Mat4f view;

    /// Combined View-Projection matrix (Projection * View)
    Maths::Mat4f VP;

    /// <summary>
    /// Updates the camera rotation based on mouse input.
    /// </summary>
    /// <param name="input">Input manager used to retrieve mouse input</param>
    void RotationUpdate(Engine::InputManager& input);

    /// <summary>
    /// Updates the forward vector based on the current camera rotation.
    /// </summary>
    void FowardUpdate();

    /// <summary>
    /// Updates the right vector based on the camera orientation.
    /// </summary>
    void RightUpdate();

    /// <summary>
    /// Updates the up vector based on the camera orientation.
    /// </summary>
    void UpUpdate();

    /// <summary>
    /// Calculates the projection matrix using perspective projection.
    /// </summary>
    void ProjectionMatrix(); // Perspective

    /// <summary>
    /// Calculates the view matrix transforming world space to camera space.
    /// </summary>
    void ViewMatrix(); // World to Camera

    /// <summary>
    /// Updates the View-Projection matrix.
    /// </summary>
    void VPMatrix(); // Projection * View

    /// <summary>
    /// Updates camera rotation using mouse movement.
    /// </summary>
    /// <param name="input">Input manager used to retrieve mouse input</param>
    void MouseUpdate(Engine::InputManager& input);

    /// <summary>
    /// Updates camera position based on keyboard input.
    /// </summary>
    /// <param name="input">Input manager used to retrieve keyboard input</param>
    void MoveUpdate(Engine::InputManager& input);

    /// <summary>
    /// Updates the global camera state including movement,
    /// rotation, and matrix calculations.
    /// </summary>
    /// <param name="input">Input manager used for camera control</param>
    void GlobalUpdate(Engine::InputManager& input);

public:

    /// <summary>
    /// Default camera constructor
    /// </summary>
    Camera();

    /// <summary>
    /// Updates the camera state.
    /// Must be implemented by derived camera classes.
    /// </summary>
    /// <param name="input">Input manager used to control the camera</param>
    virtual void Update(Engine::InputManager& input) = 0;

    /// <summary>
    /// Converts degrees to radians.
    /// </summary>
    /// <param name="degree">Angle in degrees</param>
    /// <returns>Angle in radians</returns>
    float ToRadians(float degree);

    /// <summary>
    /// Returns the projection matrix.
    /// </summary>
    /// <returns>Projection matrix</returns>
    Maths::Mat4f Getprojection() const;

    /// <summary>
    /// Returns the view matrix.
    /// </summary>
    /// <returns>View matrix</returns>
    Maths::Mat4f Getview() const;

    /// <summary>
    /// Returns the combined View-Projection matrix.
    /// </summary>
    /// <returns>View-Projection matrix</returns>
    Maths::Mat4f GetVP() const;

};