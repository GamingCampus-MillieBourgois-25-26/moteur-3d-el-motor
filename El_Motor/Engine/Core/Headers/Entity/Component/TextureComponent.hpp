#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/TextureAsset/TextureAsset.hpp"
#include "Logger/Logger.hpp"
#include "Entity/GameObject.hpp"
#include <memory>

namespace Engine {

    /// <summary>
    /// Component responsible for storing a texture associated with a GameObject.
    /// This texture can later be used by the rendering system.
    /// </summary>
    class TextureComponent : public Component {
    private:

        /// <summary>
        /// Shared pointer to the texture asset.
        /// </summary>
        std::shared_ptr<TextureAsset> m_texture;

    public:

        /// <summary>
        /// Default constructor.
        /// </summary>
        TextureComponent() = default;

        /// <summary>
        /// Returns the texture assigned to this component.
        /// </summary>
        /// <returns>Shared pointer to the TextureAsset</returns>
        std::shared_ptr<TextureAsset> GetTexture() const { return m_texture; }

        /// <summary>
        /// Assigns a texture to the GameObject.
        /// Logs the operation for debugging purposes.
        /// </summary>
        /// <param name="texture">Texture asset to assign</param>
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
        /// Releases the texture reference.
        /// </summary>
        void OnDestroy() override { m_texture.reset(); }

        /// <summary>
        /// Returns the component type name.
        /// Useful for debugging, serialization, or editor systems.
        /// </summary>
        /// <returns>Component type name</returns>
        std::string GetTypeName() const override { return "TextureRenderer"; }
    };

}