#include "Camera.hpp"

Camera::Camera() {
	position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotation = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	forward = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	right = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
	up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

	aspectRatio = 16.0f / 9.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;
	fov = DirectX::XM_PIDIV4;
}

Camera::Update();

Camera::ProjectionMatrix() const {
	return DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
}

Camera::ViewMatrix() const {
	DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&position);
	DirectX::XMVECTOR rot = DirectX::XMLoadFloat4(&rotation);

	DirectX::XMVECTOR forwardVec = DirectX::XMVector3Rotate(DirectX::XMLoadFloat3(&forward), rot);
	DirectX::XMVECTOR upVec = DirectX::XMVector3Rotate(DirectX::XMLoadFloat3(&up), rot);

	return DirectX::XMMatrixLookToLH(pos, forwardVec, upVec);
}