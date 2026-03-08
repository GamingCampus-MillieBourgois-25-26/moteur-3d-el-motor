#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/Asset.hpp"
#include <memory>
#include <string>
#include <type_traits>

namespace Engine {

    /**
     * @brief Component responsible for attaching an asset to an entity.
     *
     * This component can store meshes, textures, or any asset derived from Asset.
     * It integrates with AssetManager to load and manage assets efficiently.
     */
    class AssetComponent : public Component {
    private:

        /// @brief Pointer to the stored asset (base type for flexibility)
        std::shared_ptr<Asset> m_asset;

    public:

        /// @brief Default constructor
        AssetComponent() = default;

        /**
         * @brief Returns the stored asset casted to the requested type.
         *
         * @tparam T Requested asset type (must derive from Asset)
         * @return Shared pointer to the asset if the cast succeeds, nullptr otherwise
         */
        template<typename T>
        std::shared_ptr<T> GetAsset() const {
            return std::dynamic_pointer_cast<T>(m_asset);
        }

        /**
         * @brief Returns the raw asset pointer without casting.
         *
         * Useful when you need to access the base Asset type.
         * @return Shared pointer to the base Asset
         */
        std::shared_ptr<Asset> GetRawAsset() const {
            return m_asset;
        }

        /**
         * @brief Loads an asset from the AssetManager and stores it in this component.
         *
         * @tparam T Type of asset to load (must derive from Asset)
         * @param path Path to the asset file
         */
        template<typename T>
        void LoadAsset(const std::string& path) {
            static_assert(std::is_base_of<Asset, T>::value,
                "T must inherit from Asset");

            m_asset = AssetManager::Get().Load<T>(path);
        }

        /**
         * @brief Manually assigns an already loaded asset to this component.
         *
         * @param asset Shared pointer to the asset
         */
        void SetAsset(const std::shared_ptr<Asset>& asset) {
            m_asset = asset;
        }

        /**
         * @brief Called when the component starts.
         *
         * Override this method to implement initialization logic.
         */
        void Start() override {}

        /**
         * @brief Called every frame to update the component.
         *
         * Override this method to implement per-frame behavior.
         * @param dt Delta time between frames
         */
        void Update(float dt) override {}

        /**
         * @brief Called when the component is destroyed.
         *
         * Releases the reference to the stored asset.
         */
        void OnDestroy() override {
            m_asset.reset();
        }
    };

} // namespace Engine