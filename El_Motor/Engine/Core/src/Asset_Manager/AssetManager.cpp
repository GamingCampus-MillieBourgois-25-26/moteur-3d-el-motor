#include "Asset_Manager/AssetManager.hpp"

AssetManager& AssetManager::Get() {
    static AssetManager instance;
    return instance;
}

void AssetManager::Reload(const std::string& path) {
    auto it = m_assets.find(path);
    if (it != m_assets.end()) {
        it->second->Unload();
        it->second->Load(); 
    }
}

template<typename T>
std::shared_ptr<T> AssetManager::Load(const std::string& path)
{
    static_assert(std::is_base_of<Asset, T>::value, "T doit hériter de Asset");

    auto it = m_assets.find(path);
    if (it != m_assets.end()) {
        return std::dynamic_pointer_cast<T>(it->second);
    }

    std::shared_ptr<T> asset = std::make_shared<T>();
    asset->path = path;
    asset->Load();

    m_assets[path] = asset;
    return asset;
}

void AssetManager::UnloadAll() {
    for (auto& [path, asset] : m_assets) {
        asset->Unload();
    }
    m_assets.clear();
}

AssetManager::~AssetManager() {
    UnloadAll();
}
