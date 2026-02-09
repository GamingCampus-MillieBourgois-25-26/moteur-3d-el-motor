#pragma once
#include "../Asset.hpp"
#include <vector>
#include <DirectXMath.h>
#include <d3d11.h>

// Simple vertex struct pour DX11
struct Vertex {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;
};

class MeshAsset : public Asset {
public:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    ID3D11Buffer* vertexBuffer = nullptr;
    ID3D11Buffer* indexBuffer = nullptr;

    // Charge le OBJ et crée les buffers DX11
    void Load() override;
    void Unload() override;

private:
    void CreateBuffersDX11(); // helper interne pour GPU
};
