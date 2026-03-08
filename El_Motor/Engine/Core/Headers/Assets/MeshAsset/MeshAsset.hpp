#pragma once
#include <vector>
#include <string>
#include <d3d11.h>
#include <wrl.h>

#include "Assets/Asset.hpp"
#include "Maths/Headers/MVec2.hpp"
#include "Maths/Headers/MVec3.hpp"

namespace wrl = Microsoft::WRL;

/**
 * @brief Structure representing a simple vertex.
 *
 * Contains position, normal, and texture coordinates.
 */
struct Vertex
{
    /// Position of the vertex in 3D space
    Maths::Vec3f position;

    /// Normal vector for lighting calculations
    Maths::Vec3f normal;

    /// Texture coordinates (UV)
    Maths::Vec2f uv;
};

/**
 * @brief Asset representing a 3D mesh.
 *
 * Handles CPU and GPU data, including vertex and index buffers.
 * Inherits from Asset for integration with the engine asset pipeline.
 */
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

    /**
     * @brief Returns the mesh color
     * @return Current mesh color
     */
    const Maths::Vec3f& GetColor() const { return mColor; }

    /**
     * @brief Sets the mesh color
     * @param r Red component (0..1)
     * @param g Green component (0..1)
     * @param b Blue component (0..1)
     */
    void SetColor(float r, float g, float b) { mColor = Maths::Vec3f(r, g, b); }

    // =========================
    // Asset interface
    // =========================

    /**
     * @brief Loads the mesh from file and prepares CPU-side data
     */
    void Load() override;

    /**
     * @brief Frees CPU and GPU resources associated with the mesh
     */
    void Unload() override;

    /**
     * @brief Creates GPU vertex and index buffers
     * @param device D3D11 device used for buffer creation
     */
    void CreateBuffers(ID3D11Device* device) override;

    /**
     * @brief Binds the mesh buffers to the pipeline for rendering
     * @param context Device context used for rendering
     */
    void Bind(ID3D11DeviceContext* context) const override;

    /**
     * @brief Checks if the mesh is ready to be rendered
     * @return True if GPU buffers are valid
     */
    bool IsReady() const;

    /**
     * @brief Returns the number of indices used for DrawIndexed
     * @return Index count
     */
    UINT GetIndexCount() const;
};