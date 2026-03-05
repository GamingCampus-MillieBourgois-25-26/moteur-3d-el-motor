#pragma once

#include "Entity/Component.hpp"
#include "Logger/Logger.hpp"
#include <DirectXMath.h>

namespace Engine {

    class RigidBodyComponent : public Component {
    private:
        float m_mass = 1.0f;
        bool m_useGravity = true;

        DirectX::XMFLOAT3 m_velocity = { 0.0f, 0.0f, 0.0f };
        DirectX::XMFLOAT3 m_forces = { 0.0f, 0.0f, 0.0f };

    public:

        RigidBodyComponent() = default;

        // Getters
        float GetMass() const { return m_mass; }
        const DirectX::XMFLOAT3& GetVelocity() const { return m_velocity; }

        // Setters
        void SetMass(float mass) { m_mass = mass; }
        void SetVelocity(const DirectX::XMFLOAT3& vel) { m_velocity = vel; }

        void AddForce(const DirectX::XMFLOAT3& force)
        {
            m_forces.x += force.x;
            m_forces.y += force.y;
            m_forces.z += force.z;
        }

        void Start() override
        {
            LoggerManager::Get().LogInfo(
                "RigidBody added to GameObject: " + gameObject->GetName()
            );
        }

        void Update(float dt) override
        {
            auto* transform = gameObject->GetTransform();
            if (!transform)
                return;

            // Gravity
            if (m_useGravity)
                m_forces.y -= 9.81f * m_mass;

            // Acceleration
            DirectX::XMFLOAT3 acceleration;
            acceleration.x = m_forces.x / m_mass;
            acceleration.y = m_forces.y / m_mass;
            acceleration.z = m_forces.z / m_mass;

            // Velocity
            m_velocity.x += acceleration.x * dt;
            m_velocity.y += acceleration.y * dt;
            m_velocity.z += acceleration.z * dt;

            // Position
            auto pos = transform->GetPosition();

            pos.SetX(pos.x() + m_velocity.x * dt);
            pos.SetY(pos.y() + m_velocity.y * dt);
            pos.SetZ(pos.z() + m_velocity.z * dt);

            transform->SetPosition(pos);

            // Reset forces
            m_forces = { 0,0,0 };
        }

        void OnDestroy() override
        {
            LoggerManager::Get().LogInfo(
                "RigidBody removed from GameObject: " + gameObject->GetName()
            );
        }

        std::string GetTypeName() const override { return "RigidBody"; }
    };

}