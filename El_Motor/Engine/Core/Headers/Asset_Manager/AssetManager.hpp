#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <type_traits>
#include <iostream>

#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"
#include "Assets/MeshAsset/MeshAsset.hpp"
#include "Assets/TextureAsset/TextureAsset.hpp"

namespace wrl = Microsoft::WRL;

class AssetManager
{
public:

    static AssetManager& Get();

    void Initialize(ID3D11Device* device, ID3D11DeviceContext* context);

    template<typename T>
    std::shared_ptr<T> Load(const std::string& path) {
        static_assert(std::is_base_of<Asset, T>::value, "T doit heriter de Asset");


        // ===== MESH =====
        if constexpr (std::is_same_v<T, MeshAsset>)
        {
            auto it = m_meshes.find(path);

            if (it != m_meshes.end())
                return it->second;

            auto asset = std::make_shared<MeshAsset>();
            asset->path = path;

            asset->Load();

            if (m_device)
                asset->CreateBuffers(m_device.Get());

            m_meshes[path] = asset;

            return asset;
        }

        // ===== TEXTURE =====
        else if constexpr (std::is_same_v<T, TextureAsset>)
        {
            auto it = m_textures.find(path);

            if (it != m_textures.end())
                return it->second;

            auto asset = std::make_shared<TextureAsset>();
            asset->path = path;

            asset->Load();

            if (m_device)
                asset->CreateBuffers(m_device.Get());

            m_textures[path] = asset;

            return asset;
        }

        else
        {
            static_assert(sizeof(T) == 0, "Unsupported asset type");
        }
    }

    void Reload(const std::string& path);

    void UnloadAll();

    const std::unordered_map<std::string, std::shared_ptr<MeshAsset>>& GetMeshes() const
    {
        return m_meshes;
    }

    const std::unordered_map<std::string, std::shared_ptr<TextureAsset>>& GetTextures() const
    {
        return m_textures;
    }

    AssetManager() = default;
    ~AssetManager();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

private:

    std::unordered_map<std::string, std::shared_ptr<MeshAsset>> m_meshes;

    std::unordered_map<std::string, std::shared_ptr<TextureAsset>> m_textures;

    wrl::ComPtr<ID3D11Device> m_device = nullptr;

    wrl::ComPtr<ID3D11DeviceContext> m_context = nullptr;

};