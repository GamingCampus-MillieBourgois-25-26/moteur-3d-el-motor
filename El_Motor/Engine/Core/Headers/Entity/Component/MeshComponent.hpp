#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Logger/Logger.hpp"
#include <memory>

namespace Engine {

    /**
     * @brief Component responsible for storing and managing a mesh for an entity.
     *
     * This component is used by the rendering system to draw geometry.
     */
    class MeshComponent : public Component {
    private:

        /// @brief Shared pointer to the mesh asset associated with this component.
        std::shared_ptr<MeshAsset> m_mesh;

    public:

        /// @brief Default constructor
        MeshComponent() = default;

        /**
         * @brief Returns the mesh assigned to this component.
         * @return Shared pointer to the MeshAsset
         */
        std::shared_ptr<MeshAsset> GetMesh() const { return m_mesh; }

        /**
         * @brief Assigns a mesh to this component.
         *
         * Logs the operation for debugging purposes.
         *
         * @param mesh Mesh asset to assign
         */
        void SetMesh(std::shared_ptr<MeshAsset> mesh) {
            m_mesh = mesh;

            if (m_mesh)
            {
                Engine::LoggerManager::Get().LogInfo(
                    "Mesh Set: " + m_mesh->path
                );
            }
            else
            {
                Engine::LoggerManager::Get().LogInfo(
                    "Mesh Cleared"
                );
            }
        }

        /**
         * @brief Called when the component starts.
         *
         * Override to implement initialization logic.
         */
        void Start() override {}

        /**
         * @brief Called every frame to update the component.
         *
         * @param dt Delta time between frames
         */
        void Update(float dt) override {}

        /**
         * @brief Called when the component is destroyed.
         *
         * Releases the reference to the mesh asset.
         */
        void OnDestroy() override { m_mesh.reset(); }

        /**
         * @brief Returns the type name of the component.
         *
         * Useful for debugging, serialization, or editor systems.
         *
         * @return Component type name
         */
        std::string GetTypeName() const override { return "MeshRenderer"; }
    };

} // namespace Engine