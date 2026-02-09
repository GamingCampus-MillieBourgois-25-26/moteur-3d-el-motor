#pragma once
#include <DirectXMath.h>
#include "InputManager.hpp"

class Camera{
private:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 rotation;

	DirectX::XMFLOAT3 forward;
	DirectX::XMFLOAT3 right;
	DirectX::XMFLOAT3 up;

	float aspectRatio;
	float nearPlane;
	float farPlane;
	float fov;

	float moveSpeed;
	float sensitivity;

	DirectX::XMFLOAT4X4 projection;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 VP;
	 
protected:
	void RotationUpdate(Engine::InputManager& input);
	void FowardUpdate();
	void RightUpdate();
	void UpUpdate();

	void ProjectionMatrix();    // Persepective
	void ViewMatrix();		    // World to Camera
	void VPMatrix();			// Projection * View

	//////// GETTERS //////////

	DirectX::XMFLOAT4X4 Getprojection() const;
	DirectX::XMFLOAT4X4 Getview() const;
	DirectX::XMFLOAT4X4 GetVP() const;

public:
	Camera();

	virtual void Update(Engine::InputManager &input) = 0;
};