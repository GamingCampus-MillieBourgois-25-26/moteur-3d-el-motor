#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include <memory>

namespace Engine {

    class MeshComponent : public Component {
    private:
        std::shared_ptr<MeshAsset> m_mesh;

    public:
        MeshComponent() = default;

        std::shared_ptr<MeshAsset> GetMesh() const { return m_mesh; }

        void LoadMesh(const std::string& path) {
            m_mesh = AssetManager::Get().Load<MeshAsset>(path);
        }

        void SetMesh(std::shared_ptr<MeshAsset> mesh) {
            m_mesh = mesh;
        }

        void Start() override {}
        void Update(float dt) override {}
        void OnDestroy() override { m_mesh.reset(); }

        std::string GetTypeName() const override { return "MeshRenderer"; }
    };

}