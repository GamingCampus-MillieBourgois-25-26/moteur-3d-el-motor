#pragma once

#include "Component.hpp"

#include "Maths/Headers/MVec2.hpp"
#include "Maths/Headers/MVec3.hpp"

namespace Engine {

    /// <summary>
    /// Transform component responsible for storing spatial data of a GameObject.
    /// Defines position, rotation, and scale in 3D space.
    /// Every GameObject should have exactly one Transform.
    /// </summary>
    class Transform : public Component {
    public:

        /// <summary>
        /// Returns the component type name.
        /// </summary>
        /// <returns>Component type name</returns>
        std::string GetTypeName() const override {
            return "Transform";
        }

        /// <summary>
        /// Position of the object in world space.
        /// </summary>
        Maths::Vec3f position{};

        /// <summary>
        /// Rotation of the object (usually Euler angles).
        /// </summary>
        Maths::Vec3f rotation{};

        /// <summary>
        /// Scale of the object.
        /// Default value is (1,1,1).
        /// </summary>
        Maths::Vec3f scale{ 1.f, 1.f, 1.f };

        /// <summary>
        /// Default constructor.
        /// </summary>
        Transform() = default;

        /// <summary>
        /// Creates a transform with specified position, rotation, and scale.
        /// </summary>
        /// <param name="pos">Initial position</param>
        /// <param name="rot">Initial rotation</param>
        /// <param name="scl">Initial scale</param>
        Transform(const Maths::Vec3f& pos,
            const Maths::Vec3f& rot = Maths::Vec3f(),
            const Maths::Vec3f& scl = Maths::Vec3f(1.f, 1.f, 1.f))
            : position(pos), rotation(rot), scale(scl) {
        }

        /// <summary>
        /// Moves the object by a given offset.
        /// </summary>
        /// <param name="delta">Translation vector</param>
        void Translate(const Maths::Vec3f& delta) {
            position = position + delta;
        }

        /// <summary>
        /// Sets the world position of the object.
        /// </summary>
        /// <param name="p">New position</param>
        void SetPosition(const Maths::Vec3f& p) {
            position = p;
        }

        /// <summary>
        /// Returns the current position of the object.
        /// </summary>
        /// <returns>Reference to position vector</returns>
        const Maths::Vec3f& GetPosition() const {
            return position;
        }

        /// <summary>
        /// Called every frame to update the transform.
        /// Currently unused but kept for future logic.
        /// </summary>
        /// <param name="dt">Delta time between frames</param>
        void Update(float dt) override {
            // Empty for now
        }
    };
}