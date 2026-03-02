#include "Assets/TextureAsset/TextureAsset.hpp"

#include <stdexcept>
#include <filesystem>

#include <WICTextureLoader.h>

using namespace DirectX;

void TextureAsset::Load()
{
    if (!std::filesystem::exists(path))
        throw std::runtime_error("Texture file not found: " + path);
}

void TextureAsset::CreateBuffers(ID3D11Device* device)
{
    if (!device)
        throw std::runtime_error("Device is null");

    std::wstring wpath(path.begin(), path.end());

    HRESULT hr = CreateWICTextureFromFile(
        device,
        wpath.c_str(),
        resource.GetAddressOf(),
        shaderResourceView.GetAddressOf()
    );

    if (FAILED(hr))
        throw std::runtime_error("Failed to create texture: " + path);

    wrl::ComPtr<ID3D11Texture2D> texture;
    resource.As(&texture);

    if (texture)
    {
        D3D11_TEXTURE2D_DESC desc;
        texture->GetDesc(&desc);

        width = desc.Width;
        height = desc.Height;
    }
}

void TextureAsset::Bind(ID3D11DeviceContext* context) const
{
    if (!context)
        return;

    context->PSSetShaderResources(
        0,
        1,
        shaderResourceView.GetAddressOf()
    );
}

bool TextureAsset::IsReady() const
{
    return shaderResourceView != nullptr;
}

ID3D11ShaderResourceView* TextureAsset::GetSRV() const
{
    return shaderResourceView.Get();
}

UINT TextureAsset::GetWidth() const
{
    return width;
}

UINT TextureAsset::GetHeight() const
{
    return height;
}

void TextureAsset::Unload()
{
    shaderResourceView.Reset();
    resource.Reset();

    width = 0;
    height = 0;
}