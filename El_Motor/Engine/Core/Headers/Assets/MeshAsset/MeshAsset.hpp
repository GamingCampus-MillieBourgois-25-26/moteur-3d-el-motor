#pragma once

#include <vector>
#include <string>
#include <d3d11.h>
#include <DirectXMath.h>

#include "Assets/Asset.hpp"

struct Vertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;
};

class MeshAsset : public Asset
{
public:

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    ID3D11Buffer* vertexBuffer = nullptr;
    ID3D11Buffer* indexBuffer = nullptr;

    void Load() override;
    void Unload() override;

    

    void CreateBuffers(ID3D11Device* device);

    void Bind(ID3D11DeviceContext* context);

    void Draw(ID3D11DeviceContext* context);

    bool IsReady() const;
    UINT GetIndexCount() const;
};