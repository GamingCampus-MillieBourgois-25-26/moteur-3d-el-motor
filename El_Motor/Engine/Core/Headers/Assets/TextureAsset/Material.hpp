#pragma once

#include <memory>
#include <DirectXMath.h>
#include <d3d11.h>

#include "Assets/TextureAsset/TextureAsset.hpp"

class Material
{
public:
    Material() = default;
    ~Material() = default;

    std::shared_ptr<TextureAsset> texture = nullptr;
    DirectX::XMFLOAT3 color = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);

    bool IsReady() const
    {
        return texture && texture->IsReady();
    }

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
            ID3D11ShaderResourceView* nullSRV = nullptr;
            context->PSSetShaderResources(0, 1, &nullSRV);
        }
    }
};