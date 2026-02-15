#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/Asset.hpp"
#include <memory>
#include <string>
#include <type_traits>

namespace Engine {

    class AssetComponent : public Component {
    private:
        Asset* m_asset = nullptr;

    public:
        AssetComponent() = default;

        template<typename T>
        T* GetAsset() const {
            return dynamic_cast<T*>(m_asset);
        }

        Asset* GetRawAsset() const {
            return m_asset;
        }

        template<typename T>
        void LoadAsset(const std::string& path) {
            static_assert(std::is_base_of<Asset, T>::value, "T doit hériter de Asset");
            auto asset = AssetManager::Get().Load<T>(path);
            m_asset = asset.get();
        }

        void SetAsset(Asset* asset) {
            m_asset = asset;
        }

        void Start() override {}
        void Update(float dt) override {}
        void OnDestroy() override {
            m_asset = nullptr;
        }
    };

} // namespace Engine