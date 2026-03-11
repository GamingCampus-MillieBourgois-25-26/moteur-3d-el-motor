#pragma once

#include "Entity/Component.hpp"
#include "Logger/Logger.hpp"
#include "Maths/Headers/MVec3.hpp"
#include "Rigidbody.hpp"
#include "Colliders.hpp"

namespace Engine {
    class RigidBodyComponent : public Component {
    public:
        RigidBodyComponent() = default;
        RigidBodyComponent(PShape& shape, bool isStatic) { m_rigidBody = RigidBody(shape, isStatic); }

        void Start() override{
            LoggerManager::Get().LogInfo(
                "RigidBody added to GameObject: " + gameObject->GetName()
            );
        }

        void OnDestroy() override {
            LoggerManager::Get().LogInfo(
                "RigidBody removed from GameObject: " + gameObject->GetName()
            );
        }
        std::string GetTypeName() const override { return "RigidBody"; }

        const RigidBody& GetRigidBody() const { return m_rigidBody; }

    private:
        RigidBody m_rigidBody;
    };
}