#pragma once

#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"

namespace wrl = Microsoft::WRL;

class TextureAsset : public Asset
{
private:

    wrl::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;
    wrl::ComPtr<ID3D11Resource> resource = nullptr;

    UINT width = 0;
    UINT height = 0;

public:

    void Load() override;

    void Unload() override;

    void CreateBuffers(ID3D11Device* device) override;

    void Bind(ID3D11DeviceContext* context) const override;

    bool IsReady() const;

    ID3D11ShaderResourceView* GetSRV() const;

    UINT GetWidth() const;
    UINT GetHeight() const;
};