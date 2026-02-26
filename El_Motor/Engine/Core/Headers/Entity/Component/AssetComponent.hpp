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
        std::shared_ptr<Asset> m_asset;

    public:
        AssetComponent() = default;

        template<typename T>
        std::shared_ptr<T> GetAsset() const {
            return std::dynamic_pointer_cast<T>(m_asset);
        }

        std::shared_ptr<Asset> GetRawAsset() const {
            return m_asset;
        }

        template<typename T>
        void LoadAsset(const std::string& path) {
            static_assert(std::is_base_of<Asset, T>::value,
                "T doit hériter de Asset");

            m_asset = AssetManager::Get().Load<T>(path);
        }

        void SetAsset(const std::shared_ptr<Asset>& asset) {
            m_asset = asset;
        }

        void Start() override {}
        void Update(float dt) override {}

        void OnDestroy() override {
            m_asset.reset();
        }
    };

}