#pragma once

namespace Engine {
    class GameObject;

    class Component {
    public:
        GameObject* gameObject = nullptr;

        virtual ~Component() = default;

        virtual void Start() {}
        virtual void Update(float dt) {}
        virtual void OnDestroy() {}
        virtual std::string GetTypeName() const = 0;
    protected:
        Component() = default;
    };
}