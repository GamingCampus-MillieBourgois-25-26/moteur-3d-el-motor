#pragma once

#include "Component.hpp"
#include "Maths/Headers/MVec2.hpp"
#include "Maths/Headers/MVec3.hpp"

namespace Engine {

    /**
     * @brief Transform component responsible for storing spatial data of a GameObject.
     *
     * Defines position, rotation, and scale in 3D space.
     * Every GameObject should have exactly one Transform.
     */
    class Transform : public Component {
    public:

        /**
         * @brief Returns the component type name.
         * @return Component type name
         */
        std::string GetTypeName() const override {
            return "Transform";
        }

        /// @brief Position of the object in world space
        Maths::Vec3f position{};

        /// @brief Rotation of the object (usually Euler angles)
        Maths::Vec3f rotation{};

        /// @brief Scale of the object. Default value is (1,1,1)
        Maths::Vec3f scale{ 1.f, 1.f, 1.f };

        /**
         * @brief Default constructor
         */
        Transform() = default;

        /**
         * @brief Creates a transform with specified position, rotation, and scale
         * @param pos Initial position
         * @param rot Initial rotation (default: zero vector)
         * @param scl Initial scale (default: (1,1,1))
         */
        Transform(const Maths::Vec3f& pos,
            const Maths::Vec3f& rot = Maths::Vec3f(),
            const Maths::Vec3f& scl = Maths::Vec3f(1.f, 1.f, 1.f))
            : position(pos), rotation(rot), scale(scl) {
        }

        /**
         * @brief Moves the object by a given offset
         * @param delta Translation vector to apply
         */
        void Translate(const Maths::Vec3f& delta) {
            position = position + delta;
        }

        /**
         * @brief Sets the world position of the object
         * @param p New position vector
         */
        void SetPosition(const Maths::Vec3f& p) {
            position = p;
        }

        /**
         * @brief Returns the current position of the object
         * @return Reference to position vector
         */
        const Maths::Vec3f& GetPosition() const {
            return position;
        }

        /**
         * @brief Called every frame to update the transform
         * @param dt Delta time between frames
         *
         * Currently unused but kept for potential future logic.
         */
        void Update(float dt) override {
            // Empty for now
        }
    };

} // namespace Engine