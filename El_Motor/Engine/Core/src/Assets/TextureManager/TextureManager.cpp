#include "Assets/TextureManager/TextureManager.hpp"
#include <iostream>



TextureManager& TextureManager::Get()
{
    static TextureManager instance;
    return instance;
}

void TextureManager::Initialize(ID3D11Device* device)
{
    m_device = device;
    std::cout << "TextureManager initialized" << std::endl;
}

std::shared_ptr<TextureAsset> TextureManager::LoadTexture(const std::string& path)
{
    auto it = m_textures.find(path);
    if (it != m_textures.end())
        return it->second;

    auto texture = std::make_shared<TextureAsset>();
    texture->path = path;

    texture->Load();

    if (m_device)
        texture->CreateBuffers(m_device.Get());

    m_textures[path] = texture;
    return texture;
}

void TextureManager::Reload(const std::string& path)
{
    auto it = m_textures.find(path);
    if (it == m_textures.end())
    {
        std::cout << "Texture not found: " << path << std::endl;
        return;
    }

    it->second->Unload();
    it->second->Load();

    if (m_device)
        it->second->CreateBuffers(m_device.Get());

    std::cout << "Reloaded texture: " << path << std::endl;
}

void TextureManager::UnloadAll()
{
    for (auto& [path, tex] : m_textures)
    {
        tex->Unload();
    }

    m_textures.clear();
    std::cout << "All textures unloaded" << std::endl;
}

TextureManager::~TextureManager()
{
    UnloadAll();
}