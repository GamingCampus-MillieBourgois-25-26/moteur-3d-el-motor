#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/TextureAsset/TextureAsset.hpp"

namespace wrl = Microsoft::WRL;

/**
 * @brief Centralized texture manager.
 *
 * Responsible for loading, storing, reloading, and releasing textures.
 * Implements caching to avoid loading the same texture multiple times.
 * Acts as a singleton to provide global access to textures in the engine.
 */
class TextureManager
{
public:
    /**
     * @brief Returns the singleton instance of the TextureManager.
     * @return Reference to the unique TextureManager instance
     */
    static TextureManager& Get();

    /**
     * @brief Initializes the texture manager with a D3D11 device.
     *
     * Must be called before loading any textures.
     *
     * @param device Pointer to the D3D11 device used for texture creation
     */
    void Initialize(ID3D11Device* device);

    /**
     * @brief Loads a texture from a file.
     *
     * If the texture was previously loaded, returns the cached instance.
     *
     * @param path Path to the texture file
     * @return Shared pointer to the loaded TextureAsset
     */
    std::shared_ptr<TextureAsset> LoadTexture(const std::string& path);

    /**
     * @brief Reloads an existing texture from its file.
     *
     * Useful for updating textures after external modifications.
     *
     * @param path Path to the texture file
     */
    void Reload(const std::string& path);

    /**
     * @brief Unloads all loaded textures and clears the cache.
     */
    void UnloadAll();

    /**
     * @brief Returns the D3D11 device used by the texture manager.
     * @return Pointer to the ID3D11Device
     */
    ID3D11Device* GetDevice() const { return m_device.Get(); }

    /**
     * @brief Default constructor.
     */
    TextureManager() = default;

    /**
     * @brief Destructor. Releases all loaded textures.
     */
    ~TextureManager();

    // Disable copy and assignment
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

private:
    /**
     * @brief Internal cache storing textures indexed by file path.
     */
    std::unordered_map<std::string, std::shared_ptr<TextureAsset>> m_textures;

    /**
     * @brief D3D11 device used for creating GPU textures.
     */
    wrl::ComPtr<ID3D11Device> m_device = nullptr;
};