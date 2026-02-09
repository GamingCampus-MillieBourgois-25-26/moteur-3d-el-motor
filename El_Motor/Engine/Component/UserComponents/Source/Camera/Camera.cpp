#include "Camera.hpp"

Camera::Camera() {
	position = DirectX::XMFLOAT3(0.0f, 0.0f, 3.0f);
	rotation = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	forward = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	right = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
	up = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

	aspectRatio = 16.0f / 9.0f;
	nearPlane = 0.01f;
	farPlane = 150.0f;
	fov = DirectX::XMConvertToRadians(90.0f);
}

void Camera::RotationUpdate(Engine::InputManager& input) {
	float dx = input.getMouseDelta().x;
	float dy = input.getMouseDelta().y;

	float yaw = dx * mouseSensitivity;
	float pitch = dy * mouseSensitivity;

	XMVECTOR qYaw = DirectX::XMQuaternionRotationAxis(XMVectorSet(0,1,0,0), yaw); // Monde
	XMVECTOR qPitch = DirectX::XMQuaternionRotationAxis(right, pitch);            // Local Camera

	rotation = XMQuaternionNormalize(qPitch * qYaw * rotation);
}

void Camera::FowardUpdate() {
	forward = XMVector3Rotate(XMVectorSet(0, 0, 1, 0), rotation);
}

void Camera::RightUpdate() {
	right = XMVector3Rotate(XMVectorSet(1, 0, 0, 0), rotation);
}

void Camera::UpUpdate() {
	up = XMVector3Rotate(XMVectorSet(0, 1, 0, 0), rotation);
}

///////// CALCUL DE MATRICES //////////

void Camera::ProjectionMatrix() {
	projection = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane);
}

void Camera::ViewMatrix() {
	view = DirectX::XMMatrixLookAtLH(position, position + forward, up);
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