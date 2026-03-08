#pragma once

#include "Entity/Component.hpp"
#include "Logger/Logger.hpp"
#include <DirectXMath.h>

namespace Engine {

    /// <summary>
    /// Component responsible for basic physics simulation.
    /// Handles velocity, forces, gravity, and position updates.
    /// </summary>
    class RigidBodyComponent : public Component {
    private:

        /// <summary>
        /// Mass of the rigid body.
        /// Used to compute acceleration from applied forces.
        /// </summary>
        float m_mass = 1.0f;

        /// <summary>
        /// Determines whether gravity affects this rigid body.
        /// </summary>
        bool m_useGravity = true;

        /// <summary>
        /// Current velocity of the rigid body.
        /// </summary>
        DirectX::XMFLOAT3 m_velocity = { 0.0f, 0.0f, 0.0f };

        /// <summary>
        /// Accumulated forces applied during the frame.
        /// </summary>
        DirectX::XMFLOAT3 m_forces = { 0.0f, 0.0f, 0.0f };

    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        RigidBodyComponent() = default;

        // =========================
        // Getters
        // =========================

        /// <summary>
        /// Returns the mass of the rigid body.
        /// </summary>
        float GetMass() const { return m_mass; }

        /// <summary>
        /// Returns the current velocity.
        /// </summary>
        const DirectX::XMFLOAT3& GetVelocity() const { return m_velocity; }

        // =========================
        // Setters
        // =========================

        /// <summary>
        /// Sets the mass of the rigid body.
        /// </summary>
        /// <param name="mass">New mass value</param>
        void SetMass(float mass) { m_mass = mass; }

        /// <summary>
        /// Sets the current velocity.
        /// </summary>
        /// <param name="vel">Velocity vector</param>
        void SetVelocity(const DirectX::XMFLOAT3& vel) { m_velocity = vel; }

        /// <summary>
        /// Adds a force to the rigid body.
        /// The force will be accumulated and applied during the next update.
        /// </summary>
        /// <param name="force">Force vector</param>
        void AddForce(const DirectX::XMFLOAT3& force)
        {
            m_forces.x += force.x;
            m_forces.y += force.y;
            m_forces.z += force.z;
        }

        /// <summary>
        /// Called when the component starts.
        /// Logs that the rigid body has been attached to the GameObject.
        /// </summary>
        void Start() override
        {
            LoggerManager::Get().LogInfo(
                "RigidBody added to GameObject: " + gameObject->GetName()
            );
        }

        /// <summary>
        /// Updates the physics simulation each frame.
        /// Applies gravity, calculates acceleration,
        /// updates velocity, and moves the GameObject.
        /// </summary>
        /// <param name="dt">Delta time between frames</param>
        void Update(float dt) override
        {
            auto* transform = gameObject->GetTransform();
            if (!transform)
                return;

            // Apply gravity force
            if (m_useGravity)
                m_forces.y -= 9.81f * m_mass;

            // Compute acceleration (F = m * a)
            DirectX::XMFLOAT3 acceleration;
            acceleration.x = m_forces.x / m_mass;
            acceleration.y = m_forces.y / m_mass;
            acceleration.z = m_forces.z / m_mass;

            // Update velocity
            m_velocity.x += acceleration.x * dt;
            m_velocity.y += acceleration.y * dt;
            m_velocity.z += acceleration.z * dt;

            // Update position
            auto pos = transform->GetPosition();

            pos.SetX(pos.x() + m_velocity.x * dt);
            pos.SetY(pos.y() + m_velocity.y * dt);
            pos.SetZ(pos.z() + m_velocity.z * dt);

            transform->SetPosition(pos);

            // Reset forces after integration
            m_forces = { 0,0,0 };
        }

        /// <summary>
        /// Called when the component is destroyed.
        /// Logs that the rigid body has been removed.
        /// </summary>
        void OnDestroy() override
        {
            LoggerManager::Get().LogInfo(
                "RigidBody removed from GameObject: " + gameObject->GetName()
            );
        }

        /// <summary>
        /// Returns the type name of the component.
        /// </summary>
        /// <returns>Component type name</returns>
        std::string GetTypeName() const override { return "RigidBody"; }
    };

}