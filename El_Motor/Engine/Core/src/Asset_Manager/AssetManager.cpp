#include "Asset_Manager/AssetManager.hpp"

AssetManager& AssetManager::Get()
{
    static AssetManager instance;
    return instance;
}

void AssetManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
    m_device = device;
    m_context = context;

    std::cout << "AssetManager Initialised" << std::endl;
}

void AssetManager::Reload(const std::string& path)
{
    auto meshIt = m_meshes.find(path);

    if (meshIt != m_meshes.end())
    {
        meshIt->second->Unload();

        meshIt->second->Load();

        meshIt->second->CreateBuffers(m_device.Get());

        std::cout << "Reloaded mesh: " << path << std::endl;

        return;
    }

    auto texIt = m_textures.find(path);

    if (texIt != m_textures.end())
    {
        texIt->second->Unload();

        texIt->second->Load();

        texIt->second->CreateBuffers(m_device.Get());

        std::cout << "Reloaded texture: " << path << std::endl;

        return;
    }

    std::cout << "Asset not found for reload: " << path << std::endl;
}

void AssetManager::UnloadAll()
{
    for (auto& [path, mesh] : m_meshes)
    {
        mesh->Unload();
    }

    for (auto& [path, texture] : m_textures)
    {
        texture->Unload();
    }

    m_meshes.clear();

    m_textures.clear();

    std::cout << "All assets unloaded" << std::endl;
}

AssetManager::~AssetManager()
{
    UnloadAll();
}