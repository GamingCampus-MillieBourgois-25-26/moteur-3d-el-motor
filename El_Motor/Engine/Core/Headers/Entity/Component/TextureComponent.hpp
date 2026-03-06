#pragma once

#include "Entity/Component.hpp"
#include "Asset_Manager/AssetManager.hpp"
#include "Assets/TextureAsset/TextureAsset.hpp"
#include "Core/LoggerManager.hpp"
#include <memory>

namespace Engine {

    class TextureComponent : public Component {
    private:
        std::shared_ptr<TextureAsset> m_texture;

    public:
        TextureComponent() = default;

        std::shared_ptr<TextureAsset> GetTexture() const { return m_texture; }

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

        void Start() override {}
        void Update(float dt) override {}
        void OnDestroy() override { m_texture.reset(); }

        std::string GetTypeName() const override { return "TextureRenderer"; }
    };

}