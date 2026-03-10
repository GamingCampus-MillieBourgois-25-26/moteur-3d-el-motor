#include "Asset_Manager/AssetManager.hpp"
#include <filesystem>


AssetManager& AssetManager::Get()
{
    // Singleton global pour accéder à l'AssetManager
    static AssetManager instance;
    return instance;
}


std::shared_ptr<Material> AssetManager::LoadMaterialForMesh(const std::string& meshPath)
{
    // Extrait le nom de base et le dossier du mesh
    std::filesystem::path p(meshPath);
    std::string base = p.stem().string();
    std::string dir = p.parent_path().string();

    //Debug
    //std::cout << "Mesh path: " << meshPath << std::endl;
    //std::cout << "Directory: " << dir << std::endl;
    //std::cout << "Base name: " << base << std::endl;

    // Extensions de textures supportées
    std::vector<std::string> extensions = { ".png", ".dds", ".jpg", ".jpeg" };

    for (const auto& ext : extensions)
    {
        // Construit le chemin potentiel de la texture associée au mesh
        std::string texPath = (std::filesystem::path(dir) / (base + ext)).string();


        if (std::filesystem::exists(texPath))
        {

            // Charge la texture correspondante
            auto texture = Load<TextureAsset>(texPath);
            auto mat = std::make_shared<Material>();
            mat->texture = texture;

            return mat;
        }

    }

    // Si aucune texture trouvée, retourne un material vide
    return std::make_shared<Material>();
}

void AssetManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
    // Stocke les références au device et au context DirectX
    m_device = device;
    m_context = context;

    std::cout << "AssetManager Initialised" << std::endl;
}

void AssetManager::Reload(const std::string& path)
{
    // Vérifie si l'asset est un mesh
    auto meshIt = m_meshes.find(path);

    if (meshIt != m_meshes.end())
    {
        // Recharge complètement le mesh
        meshIt->second->Unload();

        meshIt->second->Load();

        meshIt->second->CreateBuffers(m_device.Get());

        std::cout << "Reloaded mesh: " << path << std::endl;

        return;
    }

    // Vérifie si l'asset est une texture
    auto texIt = m_textures.find(path);

    if (texIt != m_textures.end())
    {
        // Recharge complètement la texture
        texIt->second->Unload();

        texIt->second->Load();

        texIt->second->CreateBuffers(m_device.Get());

        std::cout << "Reloaded texture: " << path << std::endl;

        return;
    }

    // Aucun asset correspondant trouvé
    std::cout << "Asset not found for reload: " << path << std::endl;
}

void AssetManager::UnloadAll()
{
    // Décharge tous les meshes
    for (auto& [path, mesh] : m_meshes)
    {
        mesh->Unload();
    }

    // Décharge toutes les textures
    for (auto& [path, texture] : m_textures)
    {
        texture->Unload();
    }

    // Vide les caches
    m_meshes.clear();

    m_textures.clear();

    std::cout << "All assets unloaded" << std::endl;
}

AssetManager::~AssetManager()
{
    // Nettoyage automatique des assets à la destruction
    UnloadAll();
}