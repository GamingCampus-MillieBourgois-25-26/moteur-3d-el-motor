#pragma once
#include <string>
#include <cstdint>
#include <d3d11.h>

/**
 * @brief Unique type used to identify each asset in the engine.
 *
 * This type is used as an identifier for assets in asset managers
 * and ensures that each asset can be uniquely referenced.
 */
using AssetID = uint64_t;

/**
 * @brief Base class for all assets in the engine.
 *
 * Defines the interface for loading and unloading asset data,
 * creating GPU resources, and binding assets to the graphics pipeline.
 * All engine assets such as meshes, textures, or materials should
 * inherit from this class.
 */
class Asset {
public:

    /**
     * @brief Unique identifier of the asset.
     *
     * Used to differentiate this asset from others in the engine.
     */
    AssetID id;

    /**
     * @brief File path of the source asset.
     *
     * Stores the path from which the asset was loaded.
     * Useful for caching and reloading assets.
     */
    std::string path;

    // =========================
    // Asset interface
    // =========================

    /**
     * @brief Loads the asset data into CPU memory.
     *
     * This function must be implemented by derived classes
     * to load the asset-specific data into memory.
     */
    virtual void Load() = 0;

    /**
     * @brief Frees CPU and GPU resources associated with this asset.
     *
     * Must be implemented by derived classes. This should release
     * memory and any GPU resources allocated for the asset.
     */
    virtual void Unload() = 0;

    /**
     * @brief Creates GPU resources for the asset.
     *
     * Can be overridden by derived classes that require GPU resources
     * such as vertex buffers, index buffers, or textures.
     *
     * @param device Pointer to the D3D11 device used to create GPU resources.
     */
    virtual void CreateBuffers(ID3D11Device* device) {}

    /**
     * @brief Binds the asset to the graphics pipeline.
     *
     * Can be overridden by derived classes that need to bind
     * resources to the pipeline (e.g., textures, shaders, vertex/index buffers).
     *
     * @param context Pointer to the D3D11 device context used for rendering.
     */
    virtual void Bind(ID3D11DeviceContext* context) const {}

    /**
     * @brief Virtual destructor.
     *
     * Ensures that derived assets are properly cleaned up when deleted.
     */
    virtual ~Asset() = default;
};