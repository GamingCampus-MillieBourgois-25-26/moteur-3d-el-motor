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
void AssetManager::init() {
    std::cout << "AssetManager initialized." << std::endl;
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
