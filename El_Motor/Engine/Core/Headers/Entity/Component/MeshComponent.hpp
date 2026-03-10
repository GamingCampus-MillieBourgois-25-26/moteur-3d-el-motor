#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Logger/Logger.hpp"
#include <memory>

namespace Engine {

    /// <summary>
    /// Component responsible for storing and managing a mesh for an entity.
    /// Used by the rendering system to draw geometry.
    /// </summary>
    class MeshComponent : public Component {
    private:

        /// <summary>
        /// Shared pointer to the mesh asset associated with this component.
        /// </summary>
        std::shared_ptr<MeshAsset> m_mesh;

    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        MeshComponent() = default;

        /// <summary>
        /// Returns the mesh assigned to this component.
        /// </summary>
        /// <returns>Shared pointer to the MeshAsset</returns>
        std::shared_ptr<MeshAsset> GetMesh() const { return m_mesh; }

        /// <summary>
        /// Assigns a mesh to this component.
        /// Logs the operation for debugging purposes.
        /// </summary>
        /// <param name="mesh">Mesh asset to assign</param>
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

        /// <summary>
        /// Called when the component starts.
        /// </summary>
        void Start() override {}

        /// <summary>
        /// Called every frame to update the component.
        /// </summary>
        /// <param name="dt">Delta time between frames</param>
        void Update(float dt) override {}

        /// <summary>
        /// Called when the component is destroyed.
        /// Releases the mesh reference.
        /// </summary>
        void OnDestroy() override { m_mesh.reset(); }

        /// <summary>
        /// Returns the type name of the component.
        /// Used for debugging, serialization, or editor systems.
        /// </summary>
        /// <returns>Component type name</returns>
        std::string GetTypeName() const override { return "MeshRenderer"; }
    };

}