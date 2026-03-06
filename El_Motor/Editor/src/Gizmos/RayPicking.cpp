#include "Gizmos/RayPicking.hpp"

void RayPicking::PickObgect(float x, float y, Camera& camera, std::vector<Engine::GameObject*>& scene)
{
	mouseX = (2.0f * x) / 800  - 1.0f;
	mouseY = 1.0f - (2.0f * y) / 600;

	Maths::Quatf rayClip = { x, y, -1.0f, 1.0f };

	Maths::Quatf rayEye = Maths::Mat4f::ConvertArrayToMat4(camera.GetProjection().Inverse4x4()) * rayClip;
	rayEye = { rayEye.m_x, rayEye.m_y, -1.0f, 0.0f };

	Maths::Vec3f RayEyeVec = { rayEye.m_x, rayEye.m_y, rayEye.m_z };
	Maths::Vec3f rayWorld = (Maths::Mat4f::ConvertArrayToMat4((camera.GetView()).Inverse4x4()) * RayEyeVec).Normalized();

    Ray ray;
    ray.origin = camera.GetPosition();
    ray.direction = rayWorld;

    Engine::GameObject* selected = nullptr;
    float closest = (std::numeric_limits<float>::max)();

    for (auto entity : scene) {
        float distance;

        /*if (IntersectRayAABB(ray, entity->GetBoundingBox(), distance)) {
            if (distance < closest) {
                closest = distance;
                selected = entity;
            }
        }*/
    }
    m_selectedObject = selected;
}

bool RayPicking::IntersectRayAABB(const Ray& ray, const AABB& box, float& t) {
    float tmin = (box.min.m_x - ray.origin.m_x) / ray.direction.m_x;
    float tmax = (box.max.m_x - ray.origin.m_x) / ray.direction.m_x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (box.min.m_y - ray.origin.m_y) / ray.direction.m_y;
    float tymax = (box.max.m_y - ray.origin.m_y) / ray.direction.m_y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (box.min.m_z - ray.origin.m_z) / ray.direction.m_z;
    float tzmax = (box.max.m_z - ray.origin.m_z) / ray.direction.m_z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    t = tmin;
    return true;
}