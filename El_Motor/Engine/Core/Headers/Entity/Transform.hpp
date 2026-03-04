#pragma once

#include "Component.hpp"

#include "Maths/Headers/MVec2.hpp"
#include "Maths/Headers/MVec3.hpp"

namespace Engine {
//    struct Vec3 {
//        float x = 0.f;
//        float y = 0.f;
//        float z = 0.f;
//
//        Vec3() = default;
//        Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
//
//        Vec3 operator+(const Vec3& other) const {
//            return Vec3(x + other.x, y + other.y, z + other.z);
//        }
//
//        Vec3& operator+=(const Vec3& other) {
//            x += other.x;
//            y += other.y;
//            z += other.z;
//            return *this;
//        }
//
//        Vec3 operator-(const Vec3& other) const {
//            return Vec3(x - other.x, y - other.y, z - other.z);
//        }
//    };

    class Transform : public Component {
    public:

        std::string GetTypeName() const override {
            return "Transform";
        }

        Maths::Vec3f position{};
        Maths::Vec3f rotation{};
        Maths::Vec3f scale{ 1.f, 1.f, 1.f };

        Transform() = default;

        Transform(const Maths::Vec3f& pos,
            const Maths::Vec3f& rot = Maths::Vec3f(),
            const Maths::Vec3f& scl = Maths::Vec3f(1.f, 1.f, 1.f))
            : position(pos), rotation(rot), scale(scl) {
        }

        void Translate(const Maths::Vec3f& delta) {
            position = position + delta;
        }

        void SetPosition(const Maths::Vec3f& p) {
            position = p;
        }

        const Maths::Vec3f& GetPosition() const {
            return position;
        }

        void Update(float dt) override {
            // vide pour l'instant
        }
    };
}