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

///////// CALCUL DE MATRICES //////////

void Camera::ProjectionMatrix() {
	projection = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
}

void Camera::ViewMatrix() {
	DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&position); 
	DirectX::XMVECTOR rot = DirectX::XMLoadFloat4(&rotation);

	view = DirectX::XMMatrixRotationQuaternion(XMQuaternionInverse(rot)) * XMMatrixTranslation(-pos.x, -pos.y, -pos.z);
}

void Camera::VPMatrix() {
	VP = view * projection;
}

////////// GETTERS //////////

DirectX::XMFLOAT4X4 Camera::Getprojection() const{
	return projection;
}

DirectX::XMFLOAT4X4 Camera::Getview() const {
	return view;
}

DirectX::XMFLOAT4X4 Camera::GetVP() const{
	return VP;
}