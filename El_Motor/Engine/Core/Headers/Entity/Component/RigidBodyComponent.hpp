#pragma once

#include "Entity/Component.hpp"
#include "Logger/Logger.hpp"
#include <DirectXMath.h>

namespace Engine {

    /**
     * @brief Component responsible for basic physics simulation.
     *
     * Handles velocity, applied forces, gravity, and position updates.
     * Can be attached to any GameObject to enable physics behavior.
     */
    class RigidBodyComponent : public Component {
    private:

        /// @brief Mass of the rigid body used to compute acceleration from forces.
        float m_mass = 1.0f;

        /// @brief Determines whether gravity affects this rigid body.
        bool m_useGravity = true;

        /// @brief Current velocity of the rigid body.
        DirectX::XMFLOAT3 m_velocity = { 0.0f, 0.0f, 0.0f };

        /// @brief Accumulated forces applied during the frame.
        DirectX::XMFLOAT3 m_forces = { 0.0f, 0.0f, 0.0f };

    public:

        /// @brief Default constructor
        RigidBodyComponent() = default;

        // =========================
        // Getters
        // =========================

        /**
         * @brief Returns the mass of the rigid body.
         * @return Mass value
         */
        float GetMass() const { return m_mass; }

        /**
         * @brief Returns the current velocity of the rigid body.
         * @return Reference to the velocity vector
         */
        const DirectX::XMFLOAT3& GetVelocity() const { return m_velocity; }

        // =========================
        // Setters
        // =========================

        /**
         * @brief Sets the mass of the rigid body.
         * @param mass New mass value
         */
        void SetMass(float mass) { m_mass = mass; }

        /**
         * @brief Sets the current velocity of the rigid body.
         * @param vel Velocity vector
         */
        void SetVelocity(const DirectX::XMFLOAT3& vel) { m_velocity = vel; }

        /**
         * @brief Adds a force to the rigid body.
         *
         * The force will be accumulated and applied during the next update.
         *
         * @param force Force vector to apply
         */
        void AddForce(const DirectX::XMFLOAT3& force)
        {
            m_forces.x += force.x;
            m_forces.y += force.y;
            m_forces.z += force.z;
        }

        // =========================
        // Component Lifecycle
        // =========================

        /**
         * @brief Called when the component starts.
         *
         * Logs that the rigid body has been attached to the GameObject.
         */
        void Start() override
        {
            LoggerManager::Get().LogInfo(
                "RigidBody added to GameObject: " + gameObject->GetName()
            );
        }

        /**
         * @brief Updates the physics simulation each frame.
         *
         * Applies gravity, calculates acceleration, updates velocity,
         * and moves the GameObject accordingly.
         *
         * @param dt Delta time between frames
         */
        void Update(float dt) override
        {
            auto* transform = gameObject->GetTransform();
            if (!transform)
                return;

            // Apply gravity
            if (m_useGravity)
                m_forces.y -= 9.81f * m_mass;

            // Compute acceleration (a = F / m)
            DirectX::XMFLOAT3 acceleration;
            acceleration.x = m_forces.x / m_mass;
            acceleration.y = m_forces.y / m_mass;
            acceleration.z = m_forces.z / m_mass;

            // Update velocity
            m_velocity.x += acceleration.x * dt;
            m_velocity.y += acceleration.y * dt;
            m_velocity.z += acceleration.z * dt;

            // Update GameObject position
            auto pos = transform->GetPosition();
            pos.SetX(pos.x() + m_velocity.x * dt);
            pos.SetY(pos.y() + m_velocity.y * dt);
            pos.SetZ(pos.z() + m_velocity.z * dt);
            transform->SetPosition(pos);

            // Reset accumulated forces
            m_forces = { 0,0,0 };
        }

        /**
         * @brief Called when the component is destroyed.
         *
         * Logs that the rigid body has been removed.
         */
        void OnDestroy() override
        {
            LoggerManager::Get().LogInfo(
                "RigidBody removed from GameObject: " + gameObject->GetName()
            );
        }

        /**
         * @brief Returns the type name of the component.
         *
         * Useful for serialization or editor systems.
         *
         * @return Component type name
         */
        std::string GetTypeName() const override { return "RigidBody"; }
    };

} // namespace Engine