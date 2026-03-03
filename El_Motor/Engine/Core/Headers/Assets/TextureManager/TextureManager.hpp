#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/TextureAsset/TextureAsset.hpp"

namespace wrl = Microsoft::WRL;

class TextureManager
{
public:
    static TextureManager& Get();

    void Initialize(ID3D11Device* device);

    std::shared_ptr<TextureAsset> LoadTexture(const std::string& path);

    void Reload(const std::string& path);
    void UnloadAll();

    ID3D11Device* GetDevice() const { return m_device.Get(); }

    TextureManager() = default;
    ~TextureManager();

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

private:
    std::unordered_map<std::string, std::shared_ptr<TextureAsset>> m_textures;
    wrl::ComPtr<ID3D11Device> m_device = nullptr;
};