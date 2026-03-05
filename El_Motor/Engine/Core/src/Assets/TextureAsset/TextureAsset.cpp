#include "Assets/TextureAsset/TextureAsset.hpp"

#include <stdexcept>
#include <filesystem>

#include <WICTextureLoader.h>

using namespace DirectX;

void TextureAsset::Load()
{
    // Vérifie simplement que le fichier existe avant le chargement GPU
    if (!std::filesystem::exists(path))
        throw std::runtime_error("Texture file not found: " + path);
}

void TextureAsset::CreateBuffers(ID3D11Device* device)
{
    // Vérifie que le device DirectX est valide
    if (!device)
        throw std::runtime_error("Device is null");

    // Conversion du chemin en wchar pour l'API DirectX
    std::wstring wpath(path.begin(), path.end());

    // Création de la ressource texture + ShaderResourceView via WIC
    HRESULT hr = CreateWICTextureFromFile(
        device,
        wpath.c_str(),
        resource.GetAddressOf(),
        shaderResourceView.GetAddressOf()
    );

    if (FAILED(hr))
        throw std::runtime_error("Failed to create texture: " + path);

    // Récupération des dimensions de la texture si c'est une Texture2D
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
    // Bind la texture au slot 0 du Pixel Shader
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
    // La texture est prête si le SRV existe
    return shaderResourceView != nullptr;
}

ID3D11ShaderResourceView* TextureAsset::GetSRV() const
{
    // Accès direct au ShaderResourceView
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
    // Libère les ressources GPU
    shaderResourceView.Reset();
    resource.Reset();

    width = 0;
    height = 0;
}