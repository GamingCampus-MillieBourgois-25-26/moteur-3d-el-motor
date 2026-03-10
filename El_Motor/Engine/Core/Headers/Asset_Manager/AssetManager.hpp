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
#include "Assets/TextureAsset/Material.hpp"

namespace wrl = Microsoft::WRL;

/// <summary>
/// Central manager responsible for loading, storing, and managing all engine assets.
/// Supports meshes, textures, and materials.
/// Ensures that assets are loaded only once and reused when requested again.
/// </summary>
class AssetManager
{
public:

    /// <summary>
    /// Returns the singleton instance of the AssetManager.
    /// </summary>
    /// <returns>Reference to the AssetManager instance</returns>
    static AssetManager& Get();

    /// <summary>
    /// Initializes the AssetManager with the Direct3D device and context.
    /// These are required for creating GPU resources (buffers, textures, etc.).
    /// </summary>
    /// <param name="device">D3D11 device used to create GPU resources</param>
    /// <param name="context">D3D11 device context used for rendering</param>
    void Initialize(ID3D11Device* device, ID3D11DeviceContext* context);

    /// <summary>
    /// Loads an asset of type T from the specified path.
    /// If the asset is already loaded, returns the cached version.
    /// </summary>
    /// <typeparam name="T">Asset type (MeshAsset or TextureAsset)</typeparam>
    /// <param name="path">File path of the asset</param>
    /// <returns>Shared pointer to the loaded asset</returns>
    template<typename T>
    std::shared_ptr<T> Load(const std::string& path) {
        static_assert(std::is_base_of<Asset, T>::value, "T must inherit from Asset");


        // ===== MESH =====
        if constexpr (std::is_same_v<T, MeshAsset>)
        {
            // Check if the mesh is already loaded
            auto it = m_meshes.find(path);

            if (it != m_meshes.end())
                return it->second;

            // Create and load the mesh asset
            auto asset = std::make_shared<MeshAsset>();
            asset->path = path;

            asset->Load();

            // Create GPU buffers if a device is available
            if (m_device)
                asset->CreateBuffers(m_device.Get());

            // Store in the mesh cache
            m_meshes[path] = asset;

            return asset;
        }

        // ===== TEXTURE =====
        else if constexpr (std::is_same_v<T, TextureAsset>)
        {
            // Check if the texture is already loaded
            auto it = m_textures.find(path);

            if (it != m_textures.end())
                return it->second;

            // Create and load the texture asset
            auto asset = std::make_shared<TextureAsset>();
            asset->path = path;

            asset->Load();

            // Create GPU texture resources
            if (m_device)
                asset->CreateBuffers(m_device.Get());

            // Store in the texture cache
            m_textures[path] = asset;

            return asset;
        }

        else
        {
            static_assert(sizeof(T) == 0, "Unsupported asset type");
        }
    }

    /// <summary>
    /// Loads the material associated with a specific mesh.
    /// Typically used when meshes reference material files.
    /// </summary>
    /// <param name="meshPath">Path of the mesh</param>
    /// <returns>Shared pointer to the material</returns>
    std::shared_ptr<Material> LoadMaterialForMesh(const std::string& meshPath);

    /// <summary>
    /// Reloads an asset from disk.
    /// Useful for hot-reloading during development.
    /// </summary>
    /// <param name="path">Path of the asset to reload</param>
    void Reload(const std::string& path);

    /// <summary>
    /// Unloads all currently loaded assets and frees associated resources.
    /// </summary>
    void UnloadAll();

    /// <summary>
    /// Returns the map of all loaded meshes.
    /// </summary>
    /// <returns>Reference to the mesh asset map</returns>
    const std::unordered_map<std::string, std::shared_ptr<MeshAsset>>& GetMeshes() const
    {
        return m_meshes;
    }

    /// <summary>
    /// Returns the map of all loaded textures.
    /// </summary>
    /// <returns>Reference to the texture asset map</returns>
    const std::unordered_map<std::string, std::shared_ptr<TextureAsset>>& GetTextures() const
    {
        return m_textures;
    }

    /// <summary>
    /// Default constructor.
    /// </summary>
    AssetManager() = default;

    /// <summary>
    /// Destructor responsible for cleaning up loaded assets.
    /// </summary>
    ~AssetManager();

    /// Disable copy constructor
    AssetManager(const AssetManager&) = delete;

    /// Disable assignment operator
    AssetManager& operator=(const AssetManager&) = delete;

private:

    /// <summary>
    /// Cache storing all loaded mesh assets.
    /// Key = file path
    /// </summary>
    std::unordered_map<std::string, std::shared_ptr<MeshAsset>> m_meshes;

    /// <summary>
    /// Cache storing all loaded texture assets.
    /// Key = file path
    /// </summary>
    std::unordered_map<std::string, std::shared_ptr<TextureAsset>> m_textures;

    /// <summary>
    /// Direct3D device used to create GPU resources.
    /// </summary>
    wrl::ComPtr<ID3D11Device> m_device = nullptr;

    /// <summary>
    /// Direct3D device context used for rendering operations.
    /// </summary>
    wrl::ComPtr<ID3D11DeviceContext> m_context = nullptr;

};