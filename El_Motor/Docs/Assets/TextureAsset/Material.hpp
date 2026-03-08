#pragma once

#include <memory>
#include <DirectXMath.h>
#include <d3d11.h>

#include "Assets/TextureAsset/TextureAsset.hpp"

/// <summary>
/// Simple material class.
/// Contains a diffuse color and an optional texture.
/// Handles binding to the GPU pipeline.
/// </summary>
class Material
{
public:

    /// <summary>
    /// Default constructor
    /// </summary>
    Material() = default;

    /// <summary>
    /// Destructor
    /// </summary>
    ~Material() = default;

    // =========================
    // Material properties
    // =========================

    /// <summary>
    /// Texture associated with this material
    /// </summary>
    std::shared_ptr<TextureAsset> texture = nullptr;

    /// <summary>
    /// Diffuse color of the material (RGB, 0..1)
    /// </summary>
    DirectX::XMFLOAT3 color = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

    // =========================
    // Utility functions
    // =========================

    /// <summary>
    /// Checks if the material is ready to be used (texture loaded)
    /// </summary>
    /// <returns>True if texture exists and is ready, false otherwise</returns>
    bool IsReady() const
    {
        return texture && texture->IsReady();
    }

    /// <summary>
    /// Binds the material to the GPU pipeline.
    /// If a texture is set and ready, it will be bound.
    /// Otherwise, a null shader resource view is bound.
    /// </summary>
    /// <param name="context">Device context used for binding</param>
    void Bind(ID3D11DeviceContext* context) const
    {
        if (!context)
            return;

        if (texture && texture->IsReady())
        {
            texture->Bind(context);
        }
        else
        {
            // Bind a null SRV if no texture is available
            ID3D11ShaderResourceView* nullSRV = nullptr;
            context->PSSetShaderResources(0, 1, &nullSRV);
        }
    }
};