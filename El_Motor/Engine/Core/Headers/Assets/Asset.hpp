#pragma once
#include <string>
#include <cstdint>
#include <d3d11.h>

/// <summary>
/// Unique type used to identify each asset in the engine.
/// </summary>
using AssetID = uint64_t;

/// <summary>
/// Base class for all assets in the engine.
/// Defines the interface for loading, unloading, creating GPU resources,
/// and binding the asset to the graphics pipeline.
/// </summary>
class Asset {
public:

    /// <summary>
    /// Unique identifier of the asset
    /// </summary>
    AssetID id;

    /// <summary>
    /// File path of the source asset
    /// </summary>
    std::string path;

    // =========================
    // Asset interface
    // =========================

    /// <summary>
    /// Loads the asset data into CPU memory.
    /// Must be implemented by derived asset classes.
    /// </summary>
    virtual void Load() = 0;

    /// <summary>
    /// Frees CPU and GPU resources if applicable.
    /// Must be implemented by derived asset classes.
    /// </summary>
    virtual void Unload() = 0;

    /// <summary>
    /// Creates GPU resources for the asset (e.g., vertex/index buffers, textures).
    /// Can be overridden if the asset needs GPU-side resources.
    /// </summary>
    /// <param name="device">D3D11 device used to create GPU resources</param>
    virtual void CreateBuffers(ID3D11Device* device) {}

    /// <summary>
    /// Binds the asset to the graphics pipeline if applicable
    /// (for example, textures or meshes).
    /// </summary>
    /// <param name="context">Device context used for rendering</param>
    virtual void Bind(ID3D11DeviceContext* context) const {}

    /// <summary>
    /// Virtual destructor
    /// </summary>
    virtual ~Asset() = default;
};