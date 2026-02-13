#pragma once

class GameObject;

class Component {
public:
    GameObject* gameObject = nullptr;

    virtual ~Component() = default;

    virtual void Start() {}
    virtual void Update(float dt) {}
    virtual void OnDestroy() {}

protected:
    Component() = default;
};