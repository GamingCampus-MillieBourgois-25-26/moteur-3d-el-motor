#pragma once
#include <DirectXMath.h>

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

	DirectX::XMFLOAT4X4 projectionMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;

	DirectX::XMFLOAT4X4 VPMatrix;
	 
protected:
	///////// GETTERS //////////

	DirectX::XMMATRIX ProjectionMatrix() const; // Persepective
	DirectX::XMMATRIX ViewMatrix() const;		// World to Camera
	
	DirectX::XMMATRIX VPMatrix() const;			// Projection * View


public:
	Camera();
	Update();
};