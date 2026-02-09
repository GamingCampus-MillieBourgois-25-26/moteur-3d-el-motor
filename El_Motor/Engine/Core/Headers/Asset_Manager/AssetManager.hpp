#pragma once
#include <iostream>
#include "../Assets/Asset.hpp"
#include <memory>
#include <unordered_map>
#include <string>
#include <type_traits>
using namespace std;

class AssetManager {
public :
	static AssetManager& Get() {
		static AssetManager instance;
		return instance;
	}

    template<typename T>
    std::shared_ptr<T> Load(const std::string& path) {
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

    void Reload(const std::string& path);

    void UnloadAll();

private:
    std::unordered_map<std::string, std::shared_ptr<Asset>> m_assets;

    AssetManager() = default;
    ~AssetManager();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
};