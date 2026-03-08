#pragma once

#include <memory>
#include <DirectXMath.h>
#include <d3d11.h>

#include "Assets/TextureAsset/TextureAsset.hpp"

/**
 * @brief Simple material class.
 *
 * Contains a diffuse color and an optional texture.
 * Can be bound to the GPU pipeline for rendering.
 */
class Material
{
public:
    /**
     * @brief Default constructor
     */
    Material() = default;

    /**
     * @brief Destructor
     */
    ~Material() = default;

    // =========================
    // Material properties
    // =========================

    /// Texture associated with this material (optional)
    std::shared_ptr<TextureAsset> texture = nullptr;

    /// Diffuse color of the material (RGB, 0..1)
    DirectX::XMFLOAT3 color = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

    // =========================
    // Utility functions
    // =========================

    /**
     * @brief Checks if the material is ready to be used.
     *
     * A material is considered ready if it has a texture and the texture is ready.
     * @return true if the texture exists and is ready, false otherwise
     */
    bool IsReady() const
    {
        return texture && texture->IsReady();
    }

    /**
     * @brief Binds the material to the GPU pipeline.
     *
     * If a texture is set and ready, it will be bound to slot 0.
     * Otherwise, a null shader resource view (SRV) is bound.
     * @param context The device context used for binding
     */
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