#pragma once

#include "Component.hpp"

#include "Maths/Headers/MVec2.hpp"
#include "Maths/Headers/MVec3.hpp"
#include "Maths/Headers/MQuaternion.hpp"

namespace Engine {
    class Transform : public Component {
    public:

        std::string GetTypeName() const override {
            return "Transform";
        }

        Maths::Vec3f position;
        Maths::Quatf rotation;
        Maths::Vec3f scale;

        Transform() = default;

        Transform(const Maths::Vec3f& pos, const Maths::Quatf& rot, const Maths::Vec3f& scl) : position(pos), rotation(rot), scale(scl) {
			if (scale == Maths::Vec3f(0.0f, 0.0f, 0.0f)) Engine::Transform::SetScale(Maths::Vec3f(1.0f, 1.0f, 1.0f));
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

        void SetRotation(const Maths::Quatf& r) {
            rotation = r;
        }

        const Maths::Quatf& GetRotation() const {
            return rotation;
        }

        void SetScale(const Maths::Vec3f& s) {
            scale = s;
        }

        const Maths::Vec3f& GetScale() const {
            return scale;
        }

        void Update(float dt) override {
            // vide pour l'instant
        }
    };
}