#pragma once

#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"

namespace wrl = Microsoft::WRL;

/// <summary>
/// Asset representing a texture that can be used in the DirectX rendering pipeline.
/// Handles CPU/GPU resources, including shader resource view and underlying texture resource.
/// </summary>
class TextureAsset : public Asset
{
private:

    /// <summary>
    /// Shader Resource View (SRV) used by shaders to access the texture
    /// </summary>
    wrl::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;

    /// <summary>
    /// Underlying DirectX resource containing the texture data
    /// </summary>
    wrl::ComPtr<ID3D11Resource> resource = nullptr;

    /// <summary>
    /// Width of the texture in pixels
    /// </summary>
    UINT width = 0;

    /// <summary>
    /// Height of the texture in pixels
    /// </summary>
    UINT height = 0;

public:

    // =========================
    // Asset interface
    // =========================

    /// <summary>
    /// Loads the texture from the file associated with this asset.
    /// </summary>
    void Load() override;

    /// <summary>
    /// Releases CPU and GPU resources associated with this texture.
    /// </summary>
    void Unload() override;

    /// <summary>
    /// Creates GPU resources for the texture (SRV and underlying resource).
    /// </summary>
    /// <param name="device">D3D11 device used for creating GPU resources</param>
    void CreateBuffers(ID3D11Device* device) override;

    /// <summary>
    /// Binds the texture to the graphics pipeline.
    /// </summary>
    /// <param name="context">Device context used for rendering</param>
    void Bind(ID3D11DeviceContext* context) const override;

    /// <summary>
    /// Checks if the texture is ready to be used (SRV created and valid).
    /// </summary>
    /// <returns>True if ready</returns>
    bool IsReady() const;

    /// <summary>
    /// Returns the Shader Resource View of the texture.
    /// </summary>
    /// <returns>ID3D11ShaderResourceView pointer</returns>
    ID3D11ShaderResourceView* GetSRV() const;

    /// <summary>
    /// Returns the width of the texture in pixels.
    /// </summary>
    /// <returns>Texture width</returns>
    UINT GetWidth() const;

    /// <summary>
    /// Returns the height of the texture in pixels.
    /// </summary>
    /// <returns>Texture height</returns>
    UINT GetHeight() const;
};