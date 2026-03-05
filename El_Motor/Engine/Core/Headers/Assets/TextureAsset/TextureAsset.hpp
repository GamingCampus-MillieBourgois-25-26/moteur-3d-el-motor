#pragma once

#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"

namespace wrl = Microsoft::WRL;

// Asset représentant une texture utilisable par le pipeline DirectX
class TextureAsset : public Asset
{
private:

    // Shader Resource View utilisé par les shaders pour accéder à la texture
    wrl::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;

    // Ressource DirectX sous-jacente contenant les données de la texture
    wrl::ComPtr<ID3D11Resource> resource = nullptr;

    // Dimensions de la texture
    UINT width = 0;
    UINT height = 0;

public:

    // Charge la texture depuis le fichier associé à l'asset
    void Load() override;

    // Libère les ressources associées à la texture
    void Unload() override;

    // Crée les ressources GPU nécessaires (SRV, resource)
    void CreateBuffers(ID3D11Device* device) override;

    // Bind la texture dans le pipeline graphique
    void Bind(ID3D11DeviceContext* context) const override;

    // Indique si la texture est prête à être utilisée
    bool IsReady() const;

    // Retourne le ShaderResourceView de la texture
    ID3D11ShaderResourceView* GetSRV() const;

    // Accesseurs pour les dimensions de la texture
    UINT GetWidth() const;
    UINT GetHeight() const;
};