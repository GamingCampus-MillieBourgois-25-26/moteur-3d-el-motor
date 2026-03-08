#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/TextureAsset/TextureAsset.hpp"
#include "Logger/Logger.hpp"
#include "Entity/GameObject.hpp"
#include <memory>

namespace Engine {

    /**
     * @brief Component responsible for storing a texture associated with a GameObject.
     *
     * The texture can later be used by the rendering system to apply
     * visual appearance to the object.
     */
    class TextureComponent : public Component {
    private:

        /// @brief Shared pointer to the assigned texture asset
        std::shared_ptr<TextureAsset> m_texture;

    public:

        /// @brief Default constructor
        TextureComponent() = default;

        // =========================
        // Getters
        // =========================

        /**
         * @brief Returns the currently assigned texture.
         * @return Shared pointer to the TextureAsset
         */
        std::shared_ptr<TextureAsset> GetTexture() const { return m_texture; }

        // =========================
        // Setters
        // =========================

        /**
         * @brief Assigns a texture to the GameObject.
         *
         * Logs the operation for debugging purposes.
         * Passing nullptr clears the texture.
         *
         * @param texture Shared pointer to the TextureAsset
         */
        void SetTexture(std::shared_ptr<TextureAsset> texture)
        {
            m_texture = texture;

            if (m_texture)
            {
                LoggerManager::Get().LogInfo(
                    "Texture Set on GameObject [" + gameObject->GetName() +
                    "] : " + m_texture->path
                );
            }
            else
            {
                LoggerManager::Get().LogInfo(
                    "Texture Cleared on GameObject [" + gameObject->GetName() + "]"
                );
            }
        }

        // =========================
        // Component Lifecycle
        // =========================

        /**
         * @brief Called when the component starts.
         * Can be used for initialization logic.
         */
        void Start() override {}

        /**
         * @brief Called every frame to update the component.
         * @param dt Delta time since last frame
         */
        void Update(float dt) override {}

        /**
         * @brief Called when the component is destroyed.
         *
         * Releases the reference to the texture asset to free memory.
         */
        void OnDestroy() override { m_texture.reset(); }

        /**
         * @brief Returns the type name of the component.
         *
         * Useful for debugging, serialization, or editor systems.
         * @return Component type name
         */
        std::string GetTypeName() const override { return "TextureRenderer"; }
    };

} // namespace Engine