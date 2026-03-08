#pragma once
#include <vector>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"
#include "Maths/Headers/MVec2.hpp"
#include "Maths/Headers/MVec3.hpp"

namespace wrl = Microsoft::WRL;

/// <summary>
/// Structure representing a simple vertex.
/// Contains position, normal, and texture coordinates.
/// </summary>
struct Vertex
{
    /// Position of the vertex in 3D space
    Maths::Vec3f position;

    /// Normal vector for lighting calculations
    Maths::Vec3f normal;

    /// Texture coordinates (UV)
    Maths::Vec2f uv;
};

/// <summary>
/// Asset representing a 3D mesh.
/// Handles CPU and GPU data, including vertex and index buffers.
/// </summary>
class MeshAsset : public Asset
{
private:

    /// Color used for rendering/debugging
    Maths::Vec3f mColor = Maths::Vec3f(1.0f, 1.0f, 1.0f);

public:

    // =========================
    // CPU-side data
    // =========================

    /// Vertex data stored on CPU
    std::vector<Vertex> vertices;

    /// Index data stored on CPU
    std::vector<uint32_t> indices;

    // =========================
    // GPU-side buffers
    // =========================

    /// Vertex buffer on GPU
    wrl::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;

    /// Index buffer on GPU
    wrl::ComPtr<ID3D11Buffer> indexBuffer = nullptr;

    // =========================
    // Color accessors
    // =========================

    /// <summary>
    /// Returns the mesh color
    /// </summary>
    /// <returns>Current mesh color</returns>
    const Maths::Vec3f& GetColor() const { return mColor; }

    /// <summary>
    /// Sets the mesh color
    /// </summary>
    /// <param name="r">Red component (0..1)</param>
    /// <param name="g">Green component (0..1)</param>
    /// <param name="b">Blue component (0..1)</param>
    void SetColor(float r, float g, float b) { mColor = Maths::Vec3f(r, g, b); }

    // =========================
    // Asset interface
    // =========================

    /// <summary>
    /// Loads the mesh from file and prepares CPU data
    /// </summary>
    void Load() override;

    /// <summary>
    /// Frees CPU and GPU resources
    /// </summary>
    void Unload() override;

    /// <summary>
    /// Creates GPU vertex and index buffers
    /// </summary>
    /// <param name="device">D3D11 device used for buffer creation</param>
    void CreateBuffers(ID3D11Device* device) override;

    /// <summary>
    /// Binds the mesh buffers to the pipeline for rendering
    /// </summary>
    /// <param name="context">Device context used for rendering</param>
    void Bind(ID3D11DeviceContext* context) const override;

    /// <summary>
    /// Checks if the mesh is ready to be rendered
    /// </summary>
    /// <returns>True if GPU buffers are valid</returns>
    bool IsReady() const;

    /// <summary>
    /// Returns the number of indices used for DrawIndexed
    /// </summary>
    /// <returns>Index count</returns>
    UINT GetIndexCount() const;
};