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

/**
 * @brief Central manager responsible for loading, storing, and managing all engine assets.
 *
 * Supports meshes, textures, and materials. Ensures that assets are loaded only once
 * and reused when requested multiple times.
 */
class AssetManager
{
public:
    /**
     * @brief Returns the singleton instance of the AssetManager.
     * @return Reference to the AssetManager instance
     */
    static AssetManager& Get();

    /**
     * @brief Initializes the AssetManager with the Direct3D device and context.
     *
     * These are required for creating GPU resources (vertex/index buffers, textures, etc.).
     *
     * @param device D3D11 device used to create GPU resources
     * @param context D3D11 device context used for rendering
     */
    void Initialize(ID3D11Device* device, ID3D11DeviceContext* context);

    /**
     * @brief Loads an asset of type T from the specified path.
     *
     * If the asset is already loaded, the cached version is returned.
     * Currently supports MeshAsset and TextureAsset types.
     *
     * @tparam T Type of asset to load (must inherit from Asset)
     * @param path File path of the asset
     * @return Shared pointer to the loaded asset
     */
    template<typename T>
    std::shared_ptr<T> Load(const std::string& path) {
        static_assert(std::is_base_of<Asset, T>::value, "T must inherit from Asset");

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

    /**
     * @brief Loads the material associated with a specific mesh.
     *
     * Typically used when meshes reference material files.
     *
     * @param meshPath Path of the mesh file
     * @return Shared pointer to the loaded Material
     */
    std::shared_ptr<Material> LoadMaterialForMesh(const std::string& meshPath);

    /**
     * @brief Reloads an asset from disk.
     *
     * Useful for hot-reloading assets during development.
     *
     * @param path Path of the asset to reload
     */
    void Reload(const std::string& path);

    /**
     * @brief Unloads all currently loaded assets and frees associated resources.
     */
    void UnloadAll();

    /**
     * @brief Returns the map of all loaded meshes.
     * @return Reference to the mesh asset map
     */
    const std::unordered_map<std::string, std::shared_ptr<MeshAsset>>& GetMeshes() const
    {
        return m_meshes;
    }

    /**
     * @brief Returns the map of all loaded textures.
     * @return Reference to the texture asset map
     */
    const std::unordered_map<std::string, std::shared_ptr<TextureAsset>>& GetTextures() const
    {
        return m_textures;
    }

    /**
     * @brief Default constructor.
     */
    AssetManager() = default;

    /**
     * @brief Destructor responsible for cleaning up loaded assets.
     */
    ~AssetManager();

    /// Disable copy constructor
    AssetManager(const AssetManager&) = delete;

    /// Disable assignment operator
    AssetManager& operator=(const AssetManager&) = delete;

private:
    /// Cache storing all loaded mesh assets (key = file path)
    std::unordered_map<std::string, std::shared_ptr<MeshAsset>> m_meshes;

    /// Cache storing all loaded texture assets (key = file path)
    std::unordered_map<std::string, std::shared_ptr<TextureAsset>> m_textures;

    /// Direct3D device used to create GPU resources
    wrl::ComPtr<ID3D11Device> m_device = nullptr;

    /// Direct3D device context used for rendering operations
    wrl::ComPtr<ID3D11DeviceContext> m_context = nullptr;
};