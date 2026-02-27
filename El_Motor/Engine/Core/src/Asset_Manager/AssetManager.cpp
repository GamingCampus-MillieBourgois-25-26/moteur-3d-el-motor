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
}

void AssetManager::Reload(const std::string& path)
{
    auto it = m_assets.find(path);

    if (it != m_assets.end())
    {
        it->second->Unload();
        it->second->Load();

        if (auto mesh = std::dynamic_pointer_cast<MeshAsset>(it->second))
        {
            mesh->CreateBuffers(m_device.Get());
        }
    }
}

void AssetManager::UnloadAll()
{
    for (auto& [path, asset] : m_assets)
    {
        asset->Unload();
    }

    m_assets.clear();
}

AssetManager::~AssetManager()
{
    UnloadAll();
}