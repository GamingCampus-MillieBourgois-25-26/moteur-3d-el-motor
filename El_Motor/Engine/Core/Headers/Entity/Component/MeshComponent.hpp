#pragma once

#include "Entity/Component.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Asset_Manager/AssetManager.hpp"

#include <memory>
#include <string>

namespace Engine {

    class MeshComponent : public Component {
    private:
        std::shared_ptr<MeshAsset> m_mesh;

    public:
        MeshComponent() = default;

        // Charger un mesh depuis un fichier
        void LoadMesh(const std::string& path) {
            m_mesh = AssetManager::Get().Load<MeshAsset>(path);
        }

        // Accès au mesh
        std::shared_ptr<MeshAsset> GetMesh() const {
            return m_mesh;
        }

        MeshAsset* GetMeshRaw() const {
            return m_mesh.get();
        }

        void SetMesh(const std::shared_ptr<MeshAsset>& mesh) {
            m_mesh = mesh;
        }

        void OnDestroy() override {
            m_mesh.reset();
        }

        std::string GetTypeName() const override {
            return "MeshRenderer";
        }
    };

}