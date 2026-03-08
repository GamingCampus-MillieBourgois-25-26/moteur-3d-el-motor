#pragma once

namespace Engine {

    class GameObject;

    /**
     * @brief Base class for all components in the engine.
     *
     * Components define behaviors or functionality that can be attached to a GameObject.
     * Examples include physics, rendering, and asset management.
     */
    class Component {
    public:

        /// @brief Pointer to the GameObject that owns this component
        GameObject* gameObject = nullptr;

        /// @brief Virtual destructor to allow proper cleanup of derived components
        virtual ~Component() = default;

        /**
         * @brief Called once when the component is first initialized.
         *
         * Can be used for setup logic that depends on the GameObject or other components.
         */
        virtual void Start() {}

        /**
         * @brief Called every frame to update the component logic.
         * @param dt Delta time in seconds since the last frame
         */
        virtual void Update(float dt) {}

        /**
         * @brief Called when the component is destroyed or removed from the GameObject.
         *
         * Can be used to release resources, unregister from systems, or cleanup references.
         */
        virtual void OnDestroy() {}

        /**
         * @brief Returns the type name of the component.
         *
         * Useful for debugging, logging, or editor tools.
         * @return Component type name as a string
         */
        virtual std::string GetTypeName() const = 0;

    protected:

        /// @brief Protected constructor to prevent direct instantiation of the base Component class
        Component() = default;
    };

} // namespace Engine