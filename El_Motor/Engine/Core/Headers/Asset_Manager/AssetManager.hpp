#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <type_traits>
#include <iostream>
#include <d3d11.h>
#include "Assets/Asset.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include <wrl.h>


namespace wrl = Microsoft::WRL;

class AssetManager {
public:
    static AssetManager& Get();

    template<typename T>
    std::shared_ptr<T> Load(const std::string& path) {
        static_assert(std::is_base_of<Asset, T>::value, "T doit heriter de Asset");

        auto it = m_assets.find(path);
        if (it != m_assets.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }

        std::shared_ptr<T> asset = std::make_shared<T>();
        asset->path = path;
        asset->Load();
        if (m_device)
            asset->CreateBuffers(m_device.Get());

        m_assets[path] = asset;
        return asset;
    }
    void Initialize(ID3D11Device* device, ID3D11DeviceContext* context);
    void Reload(const std::string& path);
    void UnloadAll();

    const std::unordered_map<std::string, std::shared_ptr<Asset>>& GetAssets() const { return m_assets; }

    AssetManager() = default;
    ~AssetManager();


    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
private:
    std::unordered_map<std::string, std::shared_ptr<Asset>> m_assets;

    wrl::ComPtr<ID3D11Device> m_device = nullptr;
    wrl::ComPtr<ID3D11DeviceContext> m_context = nullptr;
   
};
