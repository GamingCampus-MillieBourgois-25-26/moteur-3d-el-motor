#include "Asset_Manager/AssetManager.hpp"
#include <filesystem>


AssetManager& AssetManager::Get()
{
    static AssetManager instance;
    return instance;
}


std::shared_ptr<Material> AssetManager::LoadMaterialForMesh(const std::string& meshPath)
{
    std::filesystem::path p(meshPath);
    std::string base = p.stem().string();
    std::string dir = p.parent_path().string();

    //Debug
    //std::cout << "Mesh path: " << meshPath << std::endl;
    //std::cout << "Directory: " << dir << std::endl;
    //std::cout << "Base name: " << base << std::endl;

    std::vector<std::string> extensions = { ".png", ".dds", ".jpg", ".jpeg" };

    for (const auto& ext : extensions)
    {
        std::string texPath = (std::filesystem::path(dir) / (base + ext)).string();


        if (std::filesystem::exists(texPath))
        {

            auto texture = Load<TextureAsset>(texPath);
            auto mat = std::make_shared<Material>();
            mat->texture = texture;

            return mat;
        }

    }
    return std::make_shared<Material>();
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