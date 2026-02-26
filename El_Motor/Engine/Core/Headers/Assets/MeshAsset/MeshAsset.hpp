#pragma once
#include <vector>
#include <string>
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

#include "Assets/Asset.hpp"

namespace wrl = Microsoft::WRL;

struct Vertex
{
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;
};

class MeshAsset : public Asset
{
private:
    DirectX::XMFLOAT3 mColor;
public:


    //MeshAsset(const std::string& path,
    //    const DirectX::XMFLOAT3& color = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f));

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    wrl::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
    wrl::ComPtr<ID3D11Buffer> indexBuffer = nullptr;

	const DirectX::XMFLOAT3& GetColor() const { return mColor; } 
    void SetColor(float r, float g, float b) { mColor = DirectX::XMFLOAT3(r, g, b); }

    void Load() override;
    void LoadTestCube();
    void Unload() override;

    

    void CreateBuffers(ID3D11Device* device);

    void Bind(ID3D11DeviceContext* context) const;

    bool IsReady() const;
    UINT GetIndexCount() const;
};