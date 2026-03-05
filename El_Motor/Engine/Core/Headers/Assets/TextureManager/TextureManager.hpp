#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/TextureAsset/TextureAsset.hpp"

namespace wrl = Microsoft::WRL;

// Gestionnaire centralisé de textures
class TextureManager
{
public:
    // Accès singleton
    static TextureManager& Get();

    // Initialise le manager avec le device D3D11
    void Initialize(ID3D11Device* device);

    // Charge une texture (cache interne)
    std::shared_ptr<TextureAsset> LoadTexture(const std::string& path);

    // Recharge une texture existante
    void Reload(const std::string& path);

    // Libère toutes les textures
    void UnloadAll();

    // Accès au device
    ID3D11Device* GetDevice() const { return m_device.Get(); }

    TextureManager() = default;
    ~TextureManager();

    // Suppression copie / assignement
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

private:
    // Stockage des textures par path
    std::unordered_map<std::string, std::shared_ptr<TextureAsset>> m_textures;

    // Device D3D11 utilisé pour la création de textures
    wrl::ComPtr<ID3D11Device> m_device = nullptr;
};