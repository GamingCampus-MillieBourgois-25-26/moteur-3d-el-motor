#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Logger/Logger.hpp"
#include <memory>

namespace Engine {

    class MeshComponent : public Component {
    private:
        std::shared_ptr<MeshAsset> m_mesh;

    public:
        MeshComponent() = default;

        std::shared_ptr<MeshAsset> GetMesh() const { return m_mesh; }

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

        void Start() override {}
        void Update(float dt) override {}
        void OnDestroy() override { m_mesh.reset(); }

        std::string GetTypeName() const override { return "MeshRenderer"; }
    };

}