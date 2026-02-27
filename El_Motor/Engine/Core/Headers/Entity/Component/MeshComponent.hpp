#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include <string>

namespace Engine {

    class MeshComponent : public Component {
    private:
        MeshAsset* m_mesh = nullptr;

    public:
        MeshComponent() = default;

        MeshAsset* GetMesh() const { return m_mesh; }

        void LoadMesh(const std::string& path) {
            auto assetPtr = AssetManager::Get().Load<MeshAsset>(path);
            m_mesh = assetPtr.get();
        }

        void SetMesh(MeshAsset* mesh) { m_mesh = mesh; }

        void Start() override {}
        void Update(float dt) override {}
        void OnDestroy() override { m_mesh = nullptr; }

        std::string GetTypeName() const override { return "MeshRenderer"; }
    };

}