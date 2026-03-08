#pragma once

#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"

namespace wrl = Microsoft::WRL;

/**
 * @brief Asset representing a GPU texture for DirectX rendering.
 *
 * Handles CPU and GPU resources, including the shader resource view (SRV)
 * and underlying DirectX resource. Supports loading, binding, and readiness checks.
 */
class TextureAsset : public Asset
{
private:
    /// Shader Resource View (SRV) for shaders to access the texture
    wrl::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;

    /// Underlying DirectX resource containing the texture data
    wrl::ComPtr<ID3D11Resource> resource = nullptr;

    /// Width of the texture in pixels
    UINT width = 0;

    /// Height of the texture in pixels
    UINT height = 0;

public:
    // =========================
    // Asset interface
    // =========================

    /**
     * @brief Loads the texture from the file associated with this asset.
     */
    void Load() override;

    /**
     * @brief Releases CPU and GPU resources for the texture.
     */
    void Unload() override;

    /**
     * @brief Creates GPU resources for the texture.
     *
     * Sets up the SRV and underlying D3D11 resource.
     * @param device D3D11 device used for resource creation
     */
    void CreateBuffers(ID3D11Device* device) override;

    /**
     * @brief Binds the texture to the graphics pipeline.
     *
     * @param context Device context used for rendering
     */
    void Bind(ID3D11DeviceContext* context) const override;

    /**
     * @brief Checks if the texture is ready to be used.
     *
     * Returns true if the SRV is valid and created.
     * @return true if ready
     */
    bool IsReady() const;

    /**
     * @brief Returns the Shader Resource View (SRV) of the texture.
     * @return ID3D11ShaderResourceView pointer
     */
    ID3D11ShaderResourceView* GetSRV() const;

    /**
     * @brief Returns the width of the texture in pixels.
     * @return Texture width
     */
    UINT GetWidth() const;

    /**
     * @brief Returns the height of the texture in pixels.
     * @return Texture height
     */
    UINT GetHeight() const;
};