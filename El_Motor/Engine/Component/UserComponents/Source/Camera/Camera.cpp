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

void Camera::MouseUpdate(Engine::InputManager& input){ // lastxy ; xyoffset ; sensitivity ; fistPos ; 

	float Xpos = input.getMousePosition().x;
	float Ypos = input.getMousePosition().y;

	float lastX = 0.f;
	float lastY = 0.f;

	if (firstMousePos) {
		lastX = Xpos;
		lastY = Ypos;

		firstMousePos = false;
	}

	float XOffset = lastX - Xpos;
	float YOffset = lastY - Ypos;

	lastX = Xpos;
	lastY = Ypos;

	XOffset *= sensitivity;
	YOffset *= sensitivity;

	float yaw += XOffset;
	float pitch += YOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	DirectX::XMFLOAT3 direction;
	direction.x = cos(DirectX::XMConvertToRadians(yaw)) * cos(DirectX::XMConvertToRadians(pitch));
	direction.y = sin(DirectX::XMConvertToRadians(pitch));
	direction.z = sin(DirectX::XMConvertToRadians(yaw)) * cos(DirectX::XMConvertToRadians(pitch));
	forward = DirectX::XMVector3Normalize(direction);
}

void Camera::GlobalUpdate(){
	FowardUpdate();
	RightUpdate();
	UpUpdate();
	MouseUpdate();
	ProjectionMatrix();
	ViewMatrix();
	VPMatrix();
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