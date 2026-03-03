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

    std::cout << "Mesh path: " << meshPath << std::endl;
    std::cout << "Directory: " << dir << std::endl;
    std::cout << "Base name: " << base << std::endl;

    std::vector<std::string> extensions = { ".png", ".dds", ".jpg", ".jpeg" };

    for (const auto& ext : extensions)
    {
        std::string texPath = (std::filesystem::path(dir) / (base + ext)).string();

        std::cout << "Testing: " << texPath;

        if (std::filesystem::exists(texPath))
        {
            std::cout << " -> FOUND" << std::endl;

            auto texture = Load<TextureAsset>(texPath);
            auto mat = std::make_shared<Material>();
            mat->texture = texture;

            return mat;
        }

        std::cout << " -> not found" << std::endl;
    }

    std::cout << "No texture found for: " << meshPath << std::endl;
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