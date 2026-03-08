#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/Asset.hpp"
#include <memory>
#include <string>
#include <type_traits>

namespace Engine {

    /// <summary>
    /// Component responsible for attaching an asset to an entity.
    /// Can store meshes, textures, or any asset derived from Asset.
    /// </summary>
    class AssetComponent : public Component {
    private:

        /// <summary>
        /// Pointer to the stored asset.
        /// Stored as the base Asset type for flexibility.
        /// </summary>
        std::shared_ptr<Asset> m_asset;

    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        AssetComponent() = default;

        /// <summary>
        /// Returns the stored asset casted to the requested type.
        /// </summary>
        /// <typeparam name="T">Requested asset type</typeparam>
        /// <returns>Shared pointer to the asset if the cast succeeds</returns>
        template<typename T>
        std::shared_ptr<T> GetAsset() const {
            return std::dynamic_pointer_cast<T>(m_asset);
        }

        /// <summary>
        /// Returns the raw asset pointer without casting.
        /// </summary>
        /// <returns>Shared pointer to the base Asset</returns>
        std::shared_ptr<Asset> GetRawAsset() const {
            return m_asset;
        }

        /// <summary>
        /// Loads an asset from the AssetManager and stores it in this component.
        /// </summary>
        /// <typeparam name="T">Type of asset to load</typeparam>
        /// <param name="path">Path to the asset file</param>
        template<typename T>
        void LoadAsset(const std::string& path) {
            static_assert(std::is_base_of<Asset, T>::value,
                "T must inherit from Asset");

            m_asset = AssetManager::Get().Load<T>(path);
        }

        /// <summary>
        /// Manually assigns an already loaded asset to this component.
        /// </summary>
        /// <param name="asset">Shared pointer to the asset</param>
        void SetAsset(const std::shared_ptr<Asset>& asset) {
            m_asset = asset;
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
        /// Releases the reference to the asset.
        /// </summary>
        void OnDestroy() override {
            m_asset.reset();
        }
    };

}