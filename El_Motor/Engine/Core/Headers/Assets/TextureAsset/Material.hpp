#pragma once

#include <memory>
#include <DirectXMath.h>
#include <d3d11.h>

#include "Assets/TextureAsset/TextureAsset.hpp"

// Material simple : couleur + texture
class Material
{
public:
    Material() = default;
    ~Material() = default;

    // Texture associée au material
    std::shared_ptr<TextureAsset> texture = nullptr;

    // Couleur diffuse du material
    DirectX::XMFLOAT3 color = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

    // Vérifie si le material est prêt à être utilisé (texture chargée)
    bool IsReady() const
    {
        return texture && texture->IsReady();
    }

    // Bind le material (texture + pipeline)
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
            // Bind un null SRV si pas de texture
            ID3D11ShaderResourceView* nullSRV = nullptr;
            context->PSSetShaderResources(0, 1, &nullSRV);
        }
    }
};