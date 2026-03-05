#pragma once
#include <vector>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"
#include "Maths/Headers/MVec2.hpp"
#include "Maths/Headers/MVec3.hpp"

namespace wrl = Microsoft::WRL;

// Structure représentant un vertex simple
struct Vertex
{
    Maths::Vec3f position;
    Maths::Vec3f normal;
    Maths::Vec2f uv;
};

// Asset représentant un mesh 3D
class MeshAsset : public Asset
{
private:
    // Couleur du mesh pour rendu/debug
    Maths::Vec3f mColor = Maths::Vec3f(1.0f, 1.0f, 1.0f);

public:
    // Données CPU
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    // Buffers GPU
    wrl::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
    wrl::ComPtr<ID3D11Buffer> indexBuffer = nullptr;

    // Accesseurs pour la couleur
    const Maths::Vec3f& GetColor() const { return mColor; }
    void SetColor(float r, float g, float b) { mColor = Maths::Vec3f(r, g, b); }

    // Charge un mesh depuis le fichier path
    void Load() override;

    // Génère un cube de test
    void LoadTestCube();

    // Libère les données CPU et GPU
    void Unload() override;

    // Crée les buffers GPU (vertex/index)
    void CreateBuffers(ID3D11Device* device) override;

    // Bind le mesh dans le pipeline
    void Bind(ID3D11DeviceContext* context) const override;

    // Indique si le mesh est prêt à être utilisé
    bool IsReady() const;

    // Nombre d'indices pour DrawIndexed
    UINT GetIndexCount() const;
};