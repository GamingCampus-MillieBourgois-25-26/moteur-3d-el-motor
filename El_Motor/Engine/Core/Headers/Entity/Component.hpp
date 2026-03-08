#pragma once

namespace Engine {

    class GameObject;

    /// <summary>
    /// Base class for all components in the engine.
    /// Components define behavior that can be attached to a GameObject.
    /// </summary>
    class Component {
    public:

        /// <summary>
        /// Pointer to the GameObject that owns this component.
        /// </summary>
        GameObject* gameObject = nullptr;

        /// <summary>
        /// Virtual destructor to allow proper cleanup of derived components.
        /// </summary>
        virtual ~Component() = default;

        /// <summary>
        /// Called once when the component is first initialized.
        /// </summary>
        virtual void Start() {}

        /// <summary>
        /// Called every frame to update the component logic.
        /// </summary>
        /// <param name="dt">Delta time between frames</param>
        virtual void Update(float dt) {}

        /// <summary>
        /// Called when the component is destroyed or removed from the GameObject.
        /// </summary>
        virtual void OnDestroy() {}

        /// <summary>
        /// Returns the name of the component type.
        /// Useful for debugging, logging, or editor systems.
        /// </summary>
        /// <returns>Component type name</returns>
        virtual std::string GetTypeName() const = 0;

    protected:

        /// <summary>
        /// Protected constructor to prevent direct instantiation of the base class.
        /// </summary>
        Component() = default;
    };

}