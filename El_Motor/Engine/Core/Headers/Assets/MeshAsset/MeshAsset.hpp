#pragma once
#include <vector>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"
#include "Maths/Headers/MVec2.hpp"
#include "Maths/Headers/MVec3.hpp"

namespace wrl = Microsoft::WRL;

struct Vertex
{
    Maths::Vec3f position;
    Maths::Vec3f normal;
    Maths::Vec2f uv;
};

class MeshAsset : public Asset
{
private:
    Maths::Vec3f mColor = Maths::Vec3f(1.0f, 1.0f, 1.0f);
public:


    //MeshAsset(const std::string& path,
    //    const Maths::Vec3f& color = Maths::Vec3f(1.0f, 0.0f, 0.0f));

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    wrl::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
    wrl::ComPtr<ID3D11Buffer> indexBuffer = nullptr;

	const Maths::Vec3f& GetColor() const { return mColor; }
    void SetColor(float r, float g, float b) { mColor = Maths::Vec3f(r, g, b); }

    void Load() override;
    void LoadTestCube();
    void Unload() override;

    

    void CreateBuffers(ID3D11Device* device) override;

    void Bind(ID3D11DeviceContext* context) const override;

    bool IsReady() const;
    UINT GetIndexCount() const;
};