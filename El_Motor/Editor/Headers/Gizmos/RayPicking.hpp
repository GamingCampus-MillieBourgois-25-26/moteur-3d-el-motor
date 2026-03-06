#pragma once

#include <limits>

#include "Window/Window.hpp"
#include "Maths/Headers/MQuaternion.hpp"
#include "Maths/Headers/MVec3.hpp"
#include "Camera/Camera.hpp"
#include "Entity/GameObject.hpp"

struct Ray {
	Maths::Vec3f origin;
	Maths::Vec3f direction;
};

struct AABB {
	Maths::Vec3f min;
	Maths::Vec3f max;
};

class RayPicking {
protected:
	float mouseX;
	float mouseY;
	Engine::GameObject* m_selectedObject;

public:
	RayPicking() = default;
	~RayPicking() = default;

	void PickObgect(float x, float y, Camera& camera, std::vector<Engine::GameObject*>& scene);
	bool IntersectRayAABB(const Ray& ray, const AABB& box, float& t);
};