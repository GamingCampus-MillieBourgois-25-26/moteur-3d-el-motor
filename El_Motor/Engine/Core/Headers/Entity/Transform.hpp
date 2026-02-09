#pragma once

#include "Component.hpp"

struct Vec3 {
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    Vec3() = default;
    Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    Vec3& operator+=(const Vec3& other) {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }
};

class Transform : public Component {
public:
    Vec3 position;
    Vec3 rotation;
    Vec3 scale{ 1.f, 1.f, 1.f };

    Transform() = default;

    Transform(const Vec3& pos, const Vec3& rot = Vec3(), const Vec3& scl = Vec3(1.f, 1.f, 1.f))
        : position(pos), rotation(rot), scale(scl) {
    }

    void Update(float dt) override {
        //
    }
};
